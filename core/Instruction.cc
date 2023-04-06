#include <cstdint>
#include <string>

#define USE_OPCODE_MACRO
#include "Instruction.hh"

static constexpr auto strLen = std::char_traits<char>::length;

static constexpr uint64_t fnv1Hash(const char* str, size_t len)
{
    size_t strlen   = len > 0 ? len : strLen(str);
    uint64_t output = 0xcbf29ce484222325ULL;
    for (size_t i = 0; i < strlen; ++i)
    {
        output *= 0x100000001b3ULL;
        output ^= (uint64_t)str[i];
    }

    return output;
}

#define O(_os, _o)         \
    case fnv1Hash(_os, 0): \
        return glosso::Opcode::_o;

danxe::Opcode danxe::strToOpcode(const char* start, size_t len)
{
    switch (fnv1Hash(start, len))
    {
        OPCODE(O)
    default:
        return danxe::Opcode::Illegal;
    }
}
#undef O

#define O(_os, _o)           \
    case glosso::Opcode::_o: \
        os << (_os);         \
        break;

std::ostream& danxe::operator<<(std::ostream& os, const Opcode& opcode)
{
    switch (opcode)
    {
        OPCODE(O)
    default:
        os << "(Illegal Opcode)";
        break;
    }
    return os;
}
#undef O

std::ostream& danxe::operator<<(std::ostream& os, const Instruction& inst)
{
    os << "{ Opcode: " << inst.opcode << ", operand: " << inst.operand << " }";
    return os;
}
