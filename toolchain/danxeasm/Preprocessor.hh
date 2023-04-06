#pragma once

#include <cstdint>
#include <filesystem>
#include <string_view>
#include <vector>

#include "Error.hh"

namespace danxe::danxeasm {
constexpr size_t INCLUDE_THRESHOLD = 100;

struct IdentPair {
    std::string_view identifier;
    std::string_view value;
};

class Preprocessor {
 public:
    Preprocessor(const char* mainFilePath, const char* source);
    Preprocessor(const std::filesystem::path& mainFilePath, const char* source);
    ~Preprocessor();

    Preprocessor(const Preprocessor&) = delete;
    Preprocessor(Preprocessor&&) = delete;
    Preprocessor& operator=(const Preprocessor&) = delete;
    Preprocessor& operator=(Preprocessor&&) = delete;

    DanxeAsmErr preprocess(char** output);

 private:
    DanxeAsmErr parseIncludes(std::string& string);
    DanxeAsmErr parseDefine();
    DanxeAsmErr pluginDefine(std::string& string, char& includeHandle);

 private:
    static std::vector<std::filesystem::path> mParents;

 private:
    std::filesystem::path mMainPath;
    const char* mSource;
    const char* mStart;
    const char* mCurrent;
    bool mIsPreprocessed;

    std::vector<IdentPair> mIdentPairs;
    bool mDefinedFstLetter[128];
    bool mIsSorted;
};
}  // namespace danxe::danxeasm
