cmake_minimum_required(VERSION 3.21)

add_library(danxecore Value.cc Instruction.cc Metadata.cc SizeInt.cc)
target_compile_options(danxecore PRIVATE -O3 -Wall -Wextra -Wpedantic -Wconversion)
