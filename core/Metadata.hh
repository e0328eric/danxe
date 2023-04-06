#pragma once

#include <cstddef>
#include <cstdint>

namespace danxe {
constexpr uint64_t MAGIC_NUMBER = 0x01a46f73736f0067ULL;  // FIXME: change magic number
constexpr uint64_t DANXE_VM_VERSION = 0x4148504c41ULL;
constexpr size_t GLOBAL_MEMORY_LOCATION = 0x20;

struct Metadata {
    uint64_t magic;
    uint64_t version;
    uint64_t procLocation;
    uint64_t globalMemLength;
};

Metadata parseMetadata(const char* data);
}  // namespace danxe
