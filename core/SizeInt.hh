#pragma once

#include <compare>
#include <cstddef>
#include <iostream>

namespace danxe {
class SizeInt {
 public:
    SizeInt();
    SizeInt(size_t num);

    std::partial_ordering operator<=>(const SizeInt& rhs) const;
    operator size_t() const;

    friend std::ostream& operator<<(std::ostream& os, const SizeInt& si);

 private:
    size_t mNum;
};

std::ostream& operator<<(std::ostream& os, const SizeInt& si);
}  // namespace danxe
