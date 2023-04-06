#pragma once

#include <iostream>

namespace danxe::danxevm {
enum class DanxeVmErr {
    Ok,
    ReadFileErr,
    ParseOpcodeErr,
    ParseOperandErr,
    StackOverflowErr,
    StackUnderflowErr,
    InvalidOpcodeExecuteErr,
    InvalidOperandErr,
    InvalidAccessInstErr,
    InvalidJumpErr,
    IllegalReturnAddressErr,
    ReadStringFailedErr,
    AllocFailedErr,
    ReallocWithNonPtrValueErr,
    FreeWithNonPtrValueErr,
    ReadWithNonPtrValueErr,
    WriteWithNonPtrValueErr,
    WriteValueErr,
    DebuggerLinenoiseErr,
};

std::ostream& operator<<(std::ostream& os, const DanxeVmErr& err);
}  // namespace danxe::danxevm
