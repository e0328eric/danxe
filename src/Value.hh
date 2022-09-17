#pragma once

#include <compare>
#include <iostream>

#include "inttype.hh"

namespace danxe
{
class Value
{
public:
    enum class Type : u8
    {
        Null = 0,
        Bool,
        UInteger,
        Integer,
        Float,
        Pointer,
    };

    // constructors
    explicit Value();
    explicit Value(bool b);
    explicit Value(u64 n);
    explicit Value(i64 n);
    explicit Value(f64 x);
    explicit Value(void* ptr);

    // Type match templates (comptime type check)
    template<Type ty> struct Typename_struct;
    template<Type ty> using Typename = typename Typename_struct<ty>::type;

    // Runtime type check
    bool isType(Type ty)
    {
        return this->mType == ty;
    }

    // getter and setter
    template<Type ty>
    auto getValue() const
    {
        if constexpr (ty == Type::Null)     return;
        if constexpr (ty == Type::Bool)     return this->mInner.bool_v;
        if constexpr (ty == Type::UInteger) return this->mInner.uint_v;
        if constexpr (ty == Type::Integer)  return this->mInner.int_v;
        if constexpr (ty == Type::Float)    return this->mInner.float_v;
        if constexpr (ty == Type::Pointer)  return this->mInner.ptr_v;
    }

    template<Type ty>
    void setValue(Typename<ty> val)
    {
        if constexpr (ty == Type::Null)     { this->mType = ty; }
        if constexpr (ty == Type::Bool)     { this->mType = ty; this->mInner.bool_v = val; }
        if constexpr (ty == Type::UInteger) { this->mType = ty; this->mInner.uint_v = val; }
        if constexpr (ty == Type::Integer)  { this->mType = ty; this->mInner.int_v = val; }
        if constexpr (ty == Type::Float)    { this->mType = ty; this->mInner.float_v = val; }
        if constexpr (ty == Type::Pointer)  { this->mType = ty; this->mInner.ptr_v = val; }
    }

    // operator overloadings
    std::partial_ordering operator<=>(const Value& rhs) const noexcept;
    bool   operator==(const Value& rhs) const noexcept;
    bool   operator!=(const Value& rhs) const noexcept;
    Value  operator+(const Value& rhs)  const noexcept;
    Value  operator-(const Value& rhs)  const noexcept;
    Value  operator*(const Value& rhs)  const noexcept;
    Value  operator/(const Value& rhs)  const noexcept;
    Value& operator+=(const Value& rhs) noexcept;
    Value& operator-=(const Value& rhs) noexcept;
    Value& operator*=(const Value& rhs) noexcept;
    Value& operator/=(const Value& rhs) noexcept;
    Value  operator&&(const Value& rhs) noexcept;
    Value  operator||(const Value& rhs) noexcept;

    // print operator
    friend std::ostream& operator<<(std::ostream& os, const Value& val);

private:
    Type mType;
    union
    {
        bool bool_v;
        u64 uint_v;
        i64 int_v;
        f64 float_v;
        void* ptr_v;
    } mInner;
};

template<Value::Type ty> struct Typename_struct                        { using type = int; };
template<>               struct Typename_struct<Value::Type::Bool>     { using type = bool; };
template<>               struct Typename_struct<Value::Type::UInteger> { using type = u64; };
template<>               struct Typename_struct<Value::Type::Integer>  { using type = i64; };
template<>               struct Typename_struct<Value::Type::Float>    { using type = f64; };
template<>               struct Typename_struct<Value::Type::Pointer>  { using type = void*; };
} // namespace danxe
