#pragma once

#include "Error.hh"

namespace danxe::danxevm {
enum class AtorType {
    CppStyle = 0,
    CStyle,
};

DanxeVmErr readFile(char** output,
                    const char* inputFilename,
                    AtorType ator = AtorType::CppStyle,
                    uint64_t* lenOutput = nullptr);
}  // namespace danxe::danxevm
