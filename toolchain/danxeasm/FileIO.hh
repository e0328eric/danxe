#pragma once

#include "Error.hh"

namespace danxe::danxeasm {
DanxeAsmErr readFile(char** output, const char* inputFilename);
}  // namespace danxe::danxeasm
