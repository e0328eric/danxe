cmake_minimum_required(VERSION 3.21)
project(danxe
    VERSION     0.1.0
    DESCRIPTION "danxe language")

# Define C and C++ standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# For the purpose to use LSP for C++
set(CMAKE_EXPORT_COMPILE_COMMANDS Yes)

# Change binary location into the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include FetchContent
include(FetchContent)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(COMPILER_FLAGS -O3 -Wall -Wextra -Wpedantic)
elseif()
    set(COMPILER_FLAGS -O0 -ggdb -Wall -Wextra -Wpedantic)
endif()

add_subdirectory(lib)
add_subdirectory(core)
add_subdirectory(toolchain/danxevm)
add_subdirectory(toolchain/danxeasm)

install(TARGETS danxevm DESTINATION ~/.local/bin)
install(TARGETS danxeasm DESTINATION ~/.local/bin)
