#pragma once

#include "inttype.hh"
#include "Value.hh"
#include "Instruction.hh"

namespace danxe
{
inline constexpr usize REGISTER_COUNT = 16;
inline constexpr usize FUNCTION_STACK_CAPACITY= 1024;

struct Flag
{
    bool carry    : 1;
    bool overflow : 1;
    bool less     : 1;
    bool great    : 1;
    bool nullify  : 1;
};

enum class HaltState : u8
{
    Running = 0,
    Ok,
    IllegalOpcodeErr,
    OperandNumberErr,
    WrongOperandErr,
};

class DanxeVm
{
public:
    explicit DanxeVm(const Instruction* inst) noexcept;
    ~DanxeVm() noexcept;

    HaltState isHalt() const;
    void run();

private:
    const Instruction* mInst;
    usize mIp;
    Flag mFlag;
    Value mRegs[REGISTER_COUNT];
    usize* mFntStack;
    usize mFntSp;
    HaltState mIsHalt;
};
} // namespace danxe
