#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string_view>

#include <fmt/core.h>

#include "Compiler.hh"
#include "Error.hh"
#include "FileIO.hh"
#include "Preprocessor.hh"

using Err = danxe::danxeasm::DanxeAsmErr;

inline constexpr const char* USAGE_MSG = "USAGE: danxeasm <input-file> [-o <output-file>]";
inline constexpr const char* VERSION = "0.1.0";

const char* findExtension(const char* fileName) {
    const char* output = fileName;

    while (*output != '\0') {
        ++output;
    }

    while (*output != '.' && output != fileName) {
        --output;
    }

    return output == fileName ? nullptr : output;
}

int main(int argc, char* argv[]) {
    Err err = Err::Ok;
    char* sourceStr = nullptr;
    auto currentPath = std::filesystem::current_path();

    // Check whether any argument is given
    if (argc < 2) {
        std::cerr << USAGE_MSG << "\n";
        std::cerr << "ERROR: no input files\n";
        return 1;
    }

    // parse --help and --version flags
    if (strncmp(argv[1], "-h", 2) == 0 || strncmp(argv[1], "--help", 6) == 0) {
        std::cout << USAGE_MSG << std::endl;
        return 0;
    }
    if (strncmp(argv[1], "-v", 2) == 0 || strncmp(argv[1], "--version", 9) == 0) {
        std::cout << VERSION << std::endl;
        return 0;
    }

    // Take an input file name and extract an extension of given one
    const char* inputFilename = argv[1];
    const char* extension = findExtension(inputFilename);

    if (extension == nullptr) {
        std::cerr << "ERROR: invalid input file\n";
        return 1;
    }

    // Define a default output file name
    std::string outputFilename =
        fmt::format("{}.dxb", std::string_view(inputFilename, extension - inputFilename));

    switch (argc) {
        case 2:
            break;

        case 3:
            std::cerr << USAGE_MSG << "\n";
            std::cerr << "ERROR: specify the output file name\n";
            return 1;

        case 4:
            if (argv[3][0] == '-') {
                std::cerr << USAGE_MSG << "\n";
                std::cerr << "ERROR: specify the output file name\n";
                return 1;
            }
            outputFilename = argv[3];
            break;

        default:
            std::cerr << USAGE_MSG << "\n";
            std::cerr << "ERROR: too many input found\n";
            return 1;
    }

    if ((err = danxe::danxeasm::readFile(&sourceStr, inputFilename)) != Err::Ok) {
        std::cout << err << std::endl;
        return 1;
    }

    char* output;
    danxe::danxeasm::Preprocessor prep{inputFilename, sourceStr};
    if ((err = prep.preprocess(&output)) != Err::Ok) {
        std::cerr << err << " while preprocessing the code\n";
        return 1;
    }

    std::filesystem::current_path(currentPath);

    // Main part
    danxe::danxeasm::Compiler compiler{output};
    if ((err = compiler.compile(outputFilename)) != Err::Ok) {
        std::cerr << err << " at line " << compiler.getCodeLine() << '\n';
        return 1;
    }

    return 0;
}
