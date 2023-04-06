cmake_minimum_required(VERSION 3.21)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(danxeasm main.cc Error.cc FileIO.cc Preprocessor.cc Compiler.cc)

target_compile_options(danxeasm PRIVATE ${COMPILE_OPTIONS})

target_include_directories(danxeasm PUBLIC ${CMAKE_SOURCE_DIR}/core fmt::fmt)
target_link_libraries(danxeasm danxecore fmt::fmt)
