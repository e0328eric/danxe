#include "Error.hh"

namespace danxe::danxeasm {
std::ostream& operator<<(std::ostream& os, const DanxeAsmErr& err) {
    switch (err) {
        case DanxeAsmErr::Ok:
            os << "";
            break;
        case DanxeAsmErr::ReadFailedErr:
            os << "ERROR: reading failed";
            break;
        case DanxeAsmErr::WriteFailedErr:
            os << "ERROR: writting failed";
            break;
        case DanxeAsmErr::InstVectorIsNullErr:
            os << "ERROR: internal bug occurs (InstVectorIsNullErr)";
            break;
        case DanxeAsmErr::InstVectorAccessErr:
            os << "ERROR: internal bug occurs (InstVectorAccessErr)";
            break;
        case DanxeAsmErr::OperandTypesCollideErr:
            os << "ERROR: internal bug occurs (OperandTypesCollideErr)";
            break;
        case DanxeAsmErr::JumpsListOverflowErr:
            os << "ERROR: too many jumps found";
            break;
        case DanxeAsmErr::GlobalMemoryOverflowErr:
            os << "ERROR: too many memories were stored";
            break;
        case DanxeAsmErr::IllegalJumpLabelNameErr:
            os << "ERROR: illegal jump label name is found";
            break;
        case DanxeAsmErr::ParseIntegerErr:
            os << "ERROR: parsing integer error";
            break;
        case DanxeAsmErr::ParseUIntegerErr:
            os << "ERROR: parsing unsigned integer error";
            break;
        case DanxeAsmErr::ParseFloatErr:
            os << "ERROR: parsing float error";
            break;
        case DanxeAsmErr::ParseCharErr:
            os << "ERROR: parsing character error";
            break;
        case DanxeAsmErr::ParseStringErr:
            os << "ERROR: parsing string error";
            break;
        case DanxeAsmErr::IllFormedInclude:
            os << "ERROR: invalid include format found";
            break;
        case DanxeAsmErr::IllFormedDefine:
            os << "ERROR: invalid define format found";
            break;
        case DanxeAsmErr::IncludeCycleFoundErr:
            os << "ERROR: include cycle was found";
            break;
    }

    return os;
}
}  // namespace danxe::danxeasm
