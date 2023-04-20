#pragma once

#include <fmt/core.h>
#include <iostream>

#define ASSERT(_expr, _msg_fmt, ...)                           \
    do {                                                       \
        if (!(_expr)) {                                        \
            std::cerr << fmt::format((_msg_fmt), __VA_ARGS__); \
            asm("int $3;");                                    \
        }                                                      \
    } while (false)

[[noreturn]] void unreachable();
