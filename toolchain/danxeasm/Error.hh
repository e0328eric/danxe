#pragma once

#include <iostream>

namespace danxe::danxeasm {
enum class DanxeAsmErr {
    Ok = 0,
    IllFormedDefine,
    IllFormedInclude,
    IncludeCycleFoundErr,
    GlobalMemoryOverflowErr,
    IllegalJumpLabelNameErr,
    InstVectorAccessErr,
    InstVectorIsNullErr,
    JumpsListOverflowErr,
    OperandTypesCollideErr,
    ParseCharErr,
    ParseFloatErr,
    ParseIntegerErr,
    ParseStringErr,
    ParseUIntegerErr,
    ReadFailedErr,
    WriteFailedErr,
};

std::ostream& operator<<(std::ostream& os, const DanxeAsmErr& err);
}  // namespace danxe::danxeasm
