#pragma once

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

namespace danxe {
// TODO: consider using std::variant instead implementing tagged union
class Value {
 public:
    enum class ValueTag : uint8_t;

 public:
    // constructors
    Value();
    explicit Value(bool);
    explicit Value(int64_t);
    explicit Value(uint64_t);
    explicit Value(double);
    explicit Value(char);
    explicit Value(const char*);
    explicit Value(std::string);
    explicit Value(std::vector<Value>);

    Value(const Value&);
    Value(Value&&);
    Value& operator=(const Value&);
    Value& operator=(Value&&);

    // destructor
    ~Value() noexcept;

    // arithmetic operations
    // NOTE: All arithmetic operations wrap the data
    Value operator+(const Value& rhs) const;
    Value operator-(const Value& rhs) const;
    Value operator*(const Value& rhs) const;
    Value operator/(const Value& rhs) const;

    friend std::ostream& operator<<(std::ostream& os, const Value& val);

 public:
    enum class ValueTag : uint8_t {
        Null = 0,
        Bool,
        Integer,
        Uinteger,
        Float,
        Char,
        String,
        Array,
    };

 private:
    union ValueValue {
     public:
        // define default constructor and destructor since they are deleted in default.
        ValueValue();
        explicit ValueValue(bool);
        explicit ValueValue(int64_t);
        explicit ValueValue(uint64_t);
        explicit ValueValue(double);
        explicit ValueValue(char);
        explicit ValueValue(std::string);
        explicit ValueValue(std::vector<Value>);
        ~ValueValue() noexcept;

     public:
        bool b;
        int64_t i;
        uint64_t ui;
        double f;
        char c;
        std::string s;
        std::vector<Value> array;
    };

    // fields of Value class
    ValueTag m_type;
    ValueValue m_inner;
};
}  // namespace danxe
