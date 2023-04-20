#include "utils.hh"

// NOTE: stolen from https://en.cppreference.com/w/cpp/utility/unreachable
[[noreturn]] void unreachable() {
#if defined(__GNUC__)  // GCC, Clang, ICC
    __builtin_unreachable();
#elif defined(_MSC_VER)  // MSVC
    __assume(false);
#endif
}
