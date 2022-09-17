#include "Value.hh"
#include "inttype.hh"

namespace danxe
{
// constructors
Value::Value()
    : mType(Value::Type::Null)
    , mInner({ .ptr_v = nullptr })
{
}

Value::Value(bool b)
    : mType(Value::Type::Bool)
    , mInner({ .bool_v = b })
{
}

Value::Value(u64 n)
    : mType(Value::Type::UInteger)
    , mInner({ .uint_v= n })
{
}

Value::Value(i64 n)
    : mType(Value::Type::Integer)
    , mInner({ .int_v= n })
{
}

Value::Value(f64 x)
    : mType(Value::Type::Float)
    , mInner({ .float_v = x })
{
}

Value::Value(void* ptr)
    : mType(Value::Type::Pointer)
    , mInner({ .ptr_v = ptr })
{
}

// helper function for overloading operators
constexpr u16 match(Value::Type ty1, Value::Type ty2)
{
    return static_cast<u16>(ty1) << 8 | static_cast<u16>(ty2);
}

// operator overloadings
std::partial_ordering Value::operator<=>(const Value& rhs) const noexcept
{
    switch(match(this->mType, rhs.mType))
    {
    case match(Value::Type::Null, Value::Type::Null):
        return std::partial_ordering::equivalent;
    case match(Value::Type::Bool, Value::Type::Bool):
        return this->mInner.bool_v <=> rhs.mInner.bool_v;
    case match(Value::Type::UInteger, Value::Type::UInteger):
        return this->mInner.uint_v <=> rhs.mInner.uint_v;
    case match(Value::Type::Integer, Value::Type::Integer):
        return this->mInner.int_v <=> rhs.mInner.int_v;
    case match(Value::Type::Float, Value::Type::Float):
        return this->mInner.float_v <=> rhs.mInner.float_v;
    default:
        return std::partial_ordering::unordered;
    }
}

bool Value::operator==(const Value& rhs) const noexcept
{
    return (*this <=> rhs) == 0;
}

bool Value::operator!=(const Value& rhs) const noexcept
{
    return (*this <=> rhs) != 0;
}
     
Value Value::operator+(const Value& rhs) const noexcept
{
    switch (match(this->mType, rhs.mType))
    {
    case match(Value::Type::UInteger, Value::Type::UInteger):
        return Value{this->mInner.uint_v + rhs.mInner.uint_v};
    case match(Value::Type::Integer, Value::Type::Integer):
        return Value{this->mInner.int_v + rhs.mInner.int_v};
    case match(Value::Type::Float, Value::Type::Float):
        return Value{this->mInner.float_v + rhs.mInner.float_v};
    default:
        return Value{};
    }
}

Value Value::operator-(const Value& rhs) const noexcept
{
    switch (match(this->mType, rhs.mType))
    {
    case match(Value::Type::UInteger, Value::Type::UInteger):
        return Value{this->mInner.uint_v - rhs.mInner.uint_v};
    case match(Value::Type::Integer, Value::Type::Integer):
        return Value{this->mInner.int_v - rhs.mInner.int_v};
    case match(Value::Type::Float, Value::Type::Float):
        return Value{this->mInner.float_v - rhs.mInner.float_v};
    default:
        return Value{};
    }
}

Value Value::operator*(const Value& rhs) const noexcept
{
    switch (match(this->mType, rhs.mType))
    {
    case match(Value::Type::UInteger, Value::Type::UInteger):
        return Value{this->mInner.uint_v * rhs.mInner.uint_v};
    case match(Value::Type::Integer, Value::Type::Integer):
        return Value{this->mInner.int_v * rhs.mInner.int_v};
    case match(Value::Type::Float, Value::Type::Float):
        return Value{this->mInner.float_v * rhs.mInner.float_v};
    default:
        return Value{};
    }
}

Value Value::operator/(const Value& rhs) const noexcept
{
    switch (match(this->mType, rhs.mType))
    {
    case match(Value::Type::UInteger, Value::Type::UInteger):
        if (rhs.mInner.uint_v == 0) return Value{};
        else return Value{this->mInner.uint_v / rhs.mInner.uint_v};
    case match(Value::Type::Integer, Value::Type::Integer):
        if (rhs.mInner.int_v == 0) return Value{};
        else return Value{this->mInner.int_v / rhs.mInner.int_v};
    case match(Value::Type::Float, Value::Type::Float):
        if (rhs.mInner.float_v == 0) return Value{};
        else return Value{this->mInner.float_v / rhs.mInner.float_v};
    default:
        return Value{};
    }
}

Value& Value::operator+=(const Value& rhs) noexcept
{
    switch (this->mType)
    {
    case Value::Type::UInteger: 
        *this = *this + rhs;                       
        break;
    case Value::Type::Integer:   
        *this = *this + rhs;                       
        break;
    case Value::Type::Float:   
        *this = *this + rhs;
        break;
    default:
        {}
    }  

    return *this;
}
Value& Value::operator-=(const Value& rhs) noexcept
{
    switch (this->mType)
    {
    case Value::Type::UInteger: 
        *this = *this - rhs;                       
        break;
    case Value::Type::Integer:   
        *this = *this - rhs;                       
        break;
    case Value::Type::Float:   
        *this = *this - rhs;
        break;
    default:
        {}
    }  

    return *this;
}

Value& Value::operator*=(const Value& rhs) noexcept
{
    switch (this->mType)
    {
    case Value::Type::UInteger: 
        *this = *this * rhs;
        break;
    case Value::Type::Integer: 
        *this = *this * rhs;
        break;
    case Value::Type::Float: 
        *this = *this * rhs;
        break;
    default:
        break;
    }

    return *this;
}

Value& Value::operator/=(const Value& rhs) noexcept
{
    switch (this->mType)
    {
    case Value::Type::UInteger: 
        *this = *this / rhs;
        break;
    case Value::Type::Integer: 
        *this = *this / rhs;
        break;
    case Value::Type::Float: 
        *this = *this / rhs;
        break;
    default:
        break;
    }

    return *this;
}

Value Value::operator&&(const Value& rhs) noexcept
{
    switch (match(this->mType, rhs.mType))
    {
        case match(Value::Type::Bool, Value::Type::Bool):
            return Value{this->mInner.bool_v && rhs.mInner.bool_v};
        default:
            return Value{};
    }
}
Value Value::operator||(const Value& rhs) noexcept
{
    switch (match(this->mType, rhs.mType))
    {
        case match(Value::Type::Bool, Value::Type::Bool):
            return Value{this->mInner.bool_v && rhs.mInner.bool_v};
        default:
            return Value{};
    }
}

std::ostream& operator<<(std::ostream& os, const Value& val)
{
    switch (val.mType)
    {
    case Value::Type::Null:
        os << "(Null)";
        break;
    case Value::Type::Bool:
        os << (val.mInner.bool_v ? "true" : "false");
        break;
    case Value::Type::UInteger:
        os << val.mInner.uint_v;
        break;
    case Value::Type::Integer:
        os << val.mInner.int_v;
        break;
    case Value::Type::Float:
        os << val.mInner.float_v;
        break;
    case Value::Type::Pointer:
        os << val.mInner.ptr_v;
        break;
    default:
        os << "???";
        break;
    }
    return os;
}
} // namespace danxe
