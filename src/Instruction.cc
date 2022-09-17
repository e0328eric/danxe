#include "Instruction.hh"

namespace danxe
{
Operand::Operand()
    : mType(Operand::Type::Null)
    , mInner({ .addr_v = 0 })
{
}

Operand::Operand(usize addr)
    : mType(Operand::Type::RegAddr)
    , mInner({ .addr_v = addr })
{
}

Operand::Operand(Value val)
    : mType(Operand::Type::Value)
    , mInner({ .value_v = val })
{
}

Operand::Type Operand::getType() const
{
    return mType;
}

Instruction::Instruction(Opcode opcode)
    : mOpcode(opcode)
    , mOperandNum(0)
    , mOperand{Operand{}, Operand{}, Operand{}}
{
}

Instruction::Instruction(Opcode opcode, Operand operand1)
    : mOpcode(opcode)
    , mOperandNum(1)
    , mOperand{operand1, Operand{}, Operand{}}
{
}

Instruction::Instruction(Opcode opcode, Operand operand1, Operand operand2)
    : mOpcode(opcode)
    , mOperandNum(2)
    , mOperand{operand1, operand2, Operand{}}
{
}

Instruction::Instruction(Opcode opcode, Operand operand1, Operand operand2, Operand operand3)
    : mOpcode(opcode)
    , mOperandNum(3)
    , mOperand{operand1, operand2, operand3}
{
}

const Opcode& Instruction::getOpcode() const
{
    return mOpcode;
}

u8 Instruction::getOperandNum() const
{
    return mOperandNum;
}
} // namespace danxe
