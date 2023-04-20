#pragma once

namespace danxe {
// clang-format off
#define OPCODE_LIST(O)  \
    O(Nop,  "nop")      \
    O(Push, "push")     \
    O(Pop,  "pop")      \
    O(Add,  "add")      \
    O(Sub,  "sub")      \
    O(Mul,  "mul")      \
    O(Div,  "div")      \
    O(Rem,  "rem")      \
    O(Halt, "halt")
// clang-format on

#define O(_op, _str) _op,
enum class Opcode {
    OPCODE_LIST(O) Illegal,
};
#undef O
}  // namespace danxe
