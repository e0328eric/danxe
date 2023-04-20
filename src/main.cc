#include <iostream>
#include <string>
#include <utility>

#include "vm/Value.hh"

int main() {
    using namespace std::string_literals;

    danxe::Value foo1(false);
    danxe::Value foo2(3LL);
    danxe::Value foo3({foo1, foo2});
    danxe::Value foo4({foo1, foo2, foo3});
    danxe::Value foo({foo4, foo4, foo3, foo4, foo4});
    std::cout << foo << '\n';

    danxe::Value bar(132LL);
    std::cout << foo2 + bar << '\n';
    std::cout << foo + bar << '\n';
}
