#pragma once

#include <string_view>

#include "inttype.hh"
#include "Value.hh"

#define OPCODE(O)           \
    O("mov"sv, Mov)         \
    O("add"sv, Add)         \
    O("print"sv, Print)     \
    O("println"sv, PrintLn) \
    O("halt"sv, Halt)

namespace danxe
{
using namespace std::literals;

#define O(_sv, _ty) _ty,
enum class Opcode : u8
{
    Nop = 0,
    OPCODE(O)
    Illegal,
};
#undef O

class Operand
{
public:
    enum class Type : u8
    {
        Null = 0,
        RegAddr,
        Value,
    };

    Operand();
    Operand(usize addr);
    Operand(Value val);

    Type getType() const;

    template<Type ty>
    auto getValue() const
    {
        if constexpr (ty == Type::Null)    { return; }
        if constexpr (ty == Type::RegAddr) { return mInner.addr_v; }
        if constexpr (ty == Type::Value)   { return mInner.value_v; }
    }

private:
    Type mType;
    union
    {
        usize addr_v;
        Value value_v;
    } mInner;
};

class Instruction
{
public:
    explicit Instruction(Opcode opcode);
    Instruction(Opcode opcode, Operand operand1);
    Instruction(Opcode opcode, Operand operand1, Operand operand2);
    Instruction(Opcode opcode, Operand operand1, Operand operand2, Operand operand3);

    const Opcode& getOpcode() const;
    u8 getOperandNum() const;

    template<usize N>
    const Operand& getOperand() const { return mOperand[N]; }

private:
    Opcode mOpcode;
    u8 mOperandNum;
    Operand mOperand[3];
};
}
