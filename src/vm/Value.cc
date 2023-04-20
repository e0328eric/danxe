#include <utility>

#include "Value.hh"
#include "utils.hh"

using namespace danxe;

// constructors (ValueValue)
Value::ValueValue::ValueValue() : b(false) {}
Value::ValueValue::ValueValue(bool b) : b(b) {}
Value::ValueValue::ValueValue(int64_t i) : i(i) {}
Value::ValueValue::ValueValue(uint64_t ui) : ui(ui) {}
Value::ValueValue::ValueValue(double f) : f(f) {}
Value::ValueValue::ValueValue(char c) : c(c) {}
Value::ValueValue::ValueValue(std::string s) : s(s) {}
Value::ValueValue::ValueValue(std::vector<Value> array) : array(array) {}
Value::ValueValue::~ValueValue() noexcept {};

// constructors (Value)
Value::Value() : m_type(ValueTag::Null), m_inner() {}
Value::Value(bool b) : m_type(ValueTag::Bool), m_inner(b) {}
Value::Value(int64_t i) : m_type(ValueTag::Integer), m_inner(i) {}
Value::Value(uint64_t ui) : m_type(ValueTag::Uinteger), m_inner(ui) {}
Value::Value(double f) : m_type(ValueTag::Float), m_inner(f) {}
Value::Value(char c) : m_type(ValueTag::Char), m_inner(c) {}
Value::Value(const char* s) : m_type(ValueTag::String), m_inner(std::string(s)) {}
Value::Value(std::string s) : m_type(ValueTag::String), m_inner(s) {}
Value::Value(std::vector<Value> array) : m_type(ValueTag::Array), m_inner(array) {}

Value::Value(const Value& val) : m_type(val.m_type), m_inner() {
    switch (val.m_type) {
        using enum Value::ValueTag;
        case Null:
            break;
        case Bool:
            this->m_inner.b = val.m_inner.b;
            break;
        case Integer:
            this->m_inner.i = val.m_inner.i;
            break;
        case Uinteger:
            this->m_inner.ui = val.m_inner.ui;
            break;
        case Float:
            this->m_inner.f = val.m_inner.f;
            break;
        case Char:
            this->m_inner.c = val.m_inner.c;
            break;
        case String:
            new (&this->m_inner.s) std::string(val.m_inner.s);
            break;
        case Array:
            new (&this->m_inner.array) std::vector<Value>(val.m_inner.array);
            break;
        default:
            unreachable();
            break;
    }
}

Value::Value(Value&& val) : m_type(val.m_type), m_inner() {
    switch (val.m_type) {
        using enum Value::ValueTag;
        case Null:
            break;
        case Bool:
            this->m_inner.b = val.m_inner.b;
            break;
        case Integer:
            this->m_inner.i = val.m_inner.i;
            break;
        case Uinteger:
            this->m_inner.ui = val.m_inner.ui;
            break;
        case Float:
            this->m_inner.f = val.m_inner.f;
            break;
        case Char:
            this->m_inner.c = val.m_inner.c;
            break;
        case String:
            new (&this->m_inner.s) std::string(std::move(val.m_inner.s));
            val.m_inner.s.clear();
            break;
        case Array:
            new (&this->m_inner.array) std::vector<Value>(std::move(val.m_inner.array));
            val.m_inner.array.clear();
            break;
        default:
            unreachable();
            break;
    }
}

Value& Value::operator=(const Value& val) {
    this->m_type = val.m_type;
    switch (val.m_type) {
        using enum Value::ValueTag;
        case Null:
            break;
        case Bool:
            this->m_inner.b = val.m_inner.b;
            break;
        case Integer:
            this->m_inner.i = val.m_inner.i;
            break;
        case Uinteger:
            this->m_inner.ui = val.m_inner.ui;
            break;
        case Float:
            this->m_inner.f = val.m_inner.f;
            break;
        case Char:
            this->m_inner.c = val.m_inner.c;
            break;
        case String:
            new (&this->m_inner.s) std::string(val.m_inner.s);
            break;
        case Array:
            new (&this->m_inner.array) std::vector<Value>(val.m_inner.array);
            break;
        default:
            unreachable();
            break;
    }

    return *this;
}

Value& Value::operator=(Value&& val) {
    this->m_type = val.m_type;
    switch (val.m_type) {
        using enum Value::ValueTag;
        case Null:
            break;
        case Bool:
            this->m_inner.b = val.m_inner.b;
            break;
        case Integer:
            this->m_inner.i = val.m_inner.i;
            break;
        case Uinteger:
            this->m_inner.ui = val.m_inner.ui;
            break;
        case Float:
            this->m_inner.f = val.m_inner.f;
            break;
        case Char:
            this->m_inner.c = val.m_inner.c;
            break;
        case String:
            new (&this->m_inner.s) std::string(std::move(val.m_inner.s));
            val.m_inner.s.clear();
            break;
        case Array:
            new (&this->m_inner.array) std::vector<Value>(std::move(val.m_inner.array));
            val.m_inner.array.clear();
            break;
        default:
            unreachable();
            break;
    }

    return *this;
}

// destructor
Value::~Value() noexcept {
    switch (this->m_type) {
        using enum Value::ValueTag;
        case Null:
            [[fallthrough]];
        case Bool:
            [[fallthrough]];
        case Integer:
            [[fallthrough]];
        case Uinteger:
            [[fallthrough]];
        case Float:
            [[fallthrough]];
        case Char:
            break;
        case String:
            this->m_inner.s.~basic_string();
            break;
        case Array:
            this->m_inner.array.~vector();
            break;
        default:
            unreachable();
            break;
    }
}

// arithmetic operations
static constexpr uint16_t match(Value::ValueTag l1, Value::ValueTag l2) {
    return static_cast<uint16_t>(l1) << 8 | static_cast<uint16_t>(l2);
}

Value Value::operator+(const Value& rhs) const {
    switch (match(this->m_type, rhs.m_type)) {
        using enum ValueTag;
        case match(Integer, Integer):
            return Value{this->m_inner.i + rhs.m_inner.i};
        case match(Uinteger, Uinteger):
            return Value{this->m_inner.ui + rhs.m_inner.ui};
        case match(Float, Float):
            return Value{this->m_inner.f + rhs.m_inner.f};
        default:
            return Value{};
    }
}

Value Value::operator-(const Value& rhs) const {
    switch (match(this->m_type, rhs.m_type)) {
        using enum ValueTag;
        case match(Integer, Integer):
            return Value{this->m_inner.i - rhs.m_inner.i};
        case match(Uinteger, Uinteger):
            return Value{this->m_inner.ui - rhs.m_inner.ui};
        case match(Float, Float):
            return Value{this->m_inner.f - rhs.m_inner.f};
        default:
            return Value{};
    }
}

Value Value::operator*(const Value& rhs) const {
    switch (match(this->m_type, rhs.m_type)) {
        using enum ValueTag;
        case match(Integer, Integer):
            return Value{this->m_inner.i * rhs.m_inner.i};
        case match(Uinteger, Uinteger):
            return Value{this->m_inner.ui * rhs.m_inner.ui};
        case match(Float, Float):
            return Value{this->m_inner.f * rhs.m_inner.f};
        default:
            return Value{};
    }
}

Value Value::operator/(const Value& rhs) const {
    switch (match(this->m_type, rhs.m_type)) {
        using enum ValueTag;
        case match(Integer, Integer):
            return Value{this->m_inner.i / rhs.m_inner.i};
        case match(Uinteger, Uinteger):
            return Value{this->m_inner.ui / rhs.m_inner.ui};
        case match(Float, Float):
            return Value{this->m_inner.f / rhs.m_inner.f};
        default:
            return Value{};
    }
}

std::ostream& danxe::operator<<(std::ostream& os, const Value& val) {
    switch (val.m_type) {
        using enum Value::ValueTag;
        case Null:
            os << "(null)";
            break;
        case Bool:
            os << (val.m_inner.b ? "true" : "false");
            break;
        case Integer:
            os << val.m_inner.i;
            break;
        case Uinteger:
            os << val.m_inner.ui;
            break;
        case Float:
            os << val.m_inner.f;
            break;
        case Char:
            os << val.m_inner.c;
            break;
        case String:
            os << val.m_inner.s;
            break;
        case Array: {
            os << "[ ";
            size_t array_len = val.m_inner.array.size();
            for (size_t i = 0; i < array_len; ++i) {
                os << val.m_inner.array[i];
                if (i + 1 < array_len) {
                    os << ", ";
                }
            }
            os << " ]";
            break;
        }
        default:
            unreachable();
            break;
    }

    return os;
}
