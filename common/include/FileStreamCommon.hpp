#pragma once

#include <fstream>
#include <cstddef>

using byte_t = uint8_t;
using word_t = uint16_t;
using dword_t = uint32_t;
using qword_t = uint64_t;

enum class BlockType : uint8_t {
    byte = sizeof(byte_t),
    word = sizeof(word_t),
    dword = sizeof(dword_t),
    qword = sizeof(qword_t)
};

inline dword_t floatToDword(const float f) {
    return *reinterpret_cast<const dword_t*>(&f);
}

namespace fileStream {
    void write(std::fstream& stream, const int64_t qword, const BlockType type);

    qword_t read(std::fstream& stream, const BlockType type);

    bool hasWriteAccess(const std::string& path);
};