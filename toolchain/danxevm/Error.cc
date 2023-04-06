#include "Error.hh"

using namespace danxe::danxevm;

std::ostream& danxe::danxevm::operator<<(std::ostream& os, const DanxeVmErr& err) {
    switch (err) {
        case DanxeVmErr::Ok:
            os << "";
            break;
        case DanxeVmErr::ReadFileErr:
            os << "ERROR: failed to read a file";
            break;
        case DanxeVmErr::ParseOpcodeErr:
            os << "ERROR: error occured while parsing an opcode";
            break;
        case DanxeVmErr::ParseOperandErr:
            os << "ERROR: error occured while parsing an operand";
            break;
        case DanxeVmErr::StackOverflowErr:
            os << "ERROR: stack overflow";
            break;
        case DanxeVmErr::StackUnderflowErr:
            os << "ERROR: stack underflow";
            break;
        case DanxeVmErr::InvalidOpcodeExecuteErr:
            os << "ERROR: invalid opcode found to execute";
            break;
        case DanxeVmErr::InvalidOperandErr:
            os << "ERROR: invalid operand is given";
            break;
        case DanxeVmErr::InvalidAccessInstErr:
            os << "ERROR: segmentation fault";
            break;
        case DanxeVmErr::InvalidJumpErr:
            os << "ERROR: segmentation fault (Jump Err)";
            break;
        case DanxeVmErr::IllegalReturnAddressErr:
            os << "ERROR: segmentation fault (Return Err)";
            break;
        case DanxeVmErr::ReadStringFailedErr:
            os << "ERROR: failed to read a string";
            break;
        case DanxeVmErr::AllocFailedErr:
            os << "ERROR: allocate memory failed";
            break;
        case DanxeVmErr::ReallocWithNonPtrValueErr:
            os << "ERROR: realloc called on the non pointer value";
            break;
        case DanxeVmErr::FreeWithNonPtrValueErr:
            os << "ERROR: free called on the non pointer value";
            break;
        case DanxeVmErr::ReadWithNonPtrValueErr:
            os << "ERROR: read called on the non pointer value";
            break;
        case DanxeVmErr::WriteWithNonPtrValueErr:
            os << "ERROR: write called on the non pointer value";
            break;
        case DanxeVmErr::WriteValueErr:
            os << "ERROR: failed to write a value on the given pointer";
            break;
        case DanxeVmErr::DebuggerLinenoiseErr:
            os << "ERROR: linenoise error occurs";
            break;
    }

    return os;
}
