#include <cstring>
#include <iostream>

#include "DanxeVm.hh"

namespace danxe
{
DanxeVm::DanxeVm(const Instruction* inst) noexcept
    : mInst(inst)
    , mIp(0)
    , mFlag()
    , mRegs()
    , mFntStack(new usize[FUNCTION_STACK_CAPACITY])
    , mFntSp(0)
    , mIsHalt(HaltState::Running)
{
    memset(mRegs, 0, sizeof(Value) * REGISTER_COUNT);
}

DanxeVm::~DanxeVm() noexcept
{
    delete[] mFntStack;
}

HaltState DanxeVm::isHalt() const
{
    return mIsHalt;
}

void DanxeVm::run()
{
    const auto& inst = mInst[mIp];

    switch (inst.getOpcode())
    {
    case Opcode::Nop:
        ++mIp;
        break;

    case Opcode::Mov:
    {
        if (inst.getOperandNum() != 2)
        {
            mIsHalt = HaltState::OperandNumberErr;
            break;
        }

        const auto& op1 = inst.getOperand<0>();
        const auto& op2 = inst.getOperand<1>();

        if (op1.getType() != Operand::Type::RegAddr
            || op2.getType() != Operand::Type::Value)
        {
            mIsHalt = HaltState::WrongOperandErr;
            break;
        }

        mRegs[op1.getValue<Operand::Type::RegAddr>()]
            = op2.getValue<Operand::Type::Value>();
        ++mIp;
        break;
    }

    case Opcode::Print:
    {
        switch (inst.getOperandNum())
        {
        case 0:
            std::cout << mRegs[0];
            ++mIp;
            break;
        case 1:
        {
            const auto& op = inst.getOperand<0>();
            switch (op.getType())
            {
            case Operand::Type::RegAddr:
                std::cout << mRegs[op.getValue<Operand::Type::RegAddr>()];
                break;
            case Operand::Type::Value:
                std::cout << op.getValue<Operand::Type::Value>();
                break;
            default:
                break;
            }
            ++mIp;
            break;
        }

        default:
            mIsHalt = HaltState::OperandNumberErr;
            break;
        }
        break;
    }

    case Opcode::PrintLn:
    {
        switch (inst.getOperandNum())
        {
        case 0:
            std::cout << mRegs[0] << '\n';
            ++mIp;
            break;
        case 1:
        {
            const auto& op = inst.getOperand<0>();
            switch (op.getType())
            {
            case Operand::Type::RegAddr:
                std::cout << mRegs[op.getValue<Operand::Type::RegAddr>()] << '\n';
                break;
            case Operand::Type::Value:
                std::cout << op.getValue<Operand::Type::Value>() << '\n';
                break;
            default:
                break;
            }
            ++mIp;
            break;
        }

        default:
            mIsHalt = HaltState::OperandNumberErr;
            break;
        }
        break;
    }

    case Opcode::Halt:
        mIsHalt = HaltState::Ok;
        break;

    default:
        mIsHalt = HaltState::IllegalOpcodeErr;
        break;
    }
}
} // namespace danxe
