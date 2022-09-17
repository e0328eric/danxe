cmake_minimum_required(VERSION 3.21)

project(danxe-language)

set(CMAKE_CXX_STANDARD 20)

set(CLANG_WARNING_FLAGS
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wsign-conversion
)

if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(DEFAULT_COMPILER_OPTIONS -O3 ${CMAKE_WARNING_FLAGS})
else()
    set(DEFAULT_COMPILER_OPTIONS -O0 -ggdb ${CMAKE_WARNING_FLAGS})
endif()

add_subdirectory(lib)

add_executable(dxevm
    src/main.cc src/Value.cc src/Instruction.cc src/DanxeVm.cc)

# add_subdirectory(core)
# add_subdirectory(toolchain/dxevm)
# add_subdirectory(toolchain/danxe)

# install(TARGETS dxevm DESTINATION ~/.local/bin)
# install(TARGETS danxe DESTINATION ~/.local/bin)

