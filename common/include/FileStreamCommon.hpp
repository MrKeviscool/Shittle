#pragma once

#include <fstream>
#include <cstdint>
#include <cstring>

#include "Bigger.hpp"

using byte_t = uint8_t;
using word_t = uint16_t;
using dword_t = uint32_t;
using qword_t = uint64_t;

using byteOffset_t = dword_t;

enum class BlockType : uint8_t {
    byte = sizeof(byte_t),
    word = sizeof(word_t),
    dword = sizeof(dword_t),
    qword = sizeof(qword_t)
};

inline dword_t floatToDword(const float f) {
    dword_t d = 0;
    std::memcpy(&d, &f, sizeof(Smaller<decltype(d), decltype(f)>::type));
    return d;
}

inline float dwordtoFloat(const dword_t d) {
    float f = 0.f;
    std::memcpy(&f, &d, sizeof(Smaller<decltype(d), decltype(f)>::type));
    return f;
}

namespace fileStream {
    void write(std::fstream& stream, const qword_t size, const BlockType type);
    bool hasWriteAccess(const std::string& path);

    template<typename T, typename std::enable_if<std::is_integral<T>::value, void>::type* = nullptr> 
    void write(std::fstream& stream, const T data) {
        constexpr const byte_t size = sizeof(T);
        for (byte_t i = 0; i < size; i++) {
            const char toPut = (data >> (((size - 1) - i) * 8)) & 0xFF;
            stream.put(toPut);
        }
    }

    template<typename T, typename std::enable_if<std::is_integral<T>::value, void>::type* = nullptr> 
    T read(std::fstream& stream) {
        const byte_t size = sizeof(T);
        T out = 0;
        for (byte_t i = 0; i < size; i++) {
            int tmp = stream.get();
            if (tmp == std::char_traits<char>::eof()) throw std::exception();
            out |= tmp;
            out <<= (i * 8);
        }
        return out;
    }
};
