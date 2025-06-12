#include "FileStreamCommon.hpp"

namespace file {
    void write(std::fstream& stream, const int64_t qword, const BlockType type) {
        const int8_t size = static_cast<int8_t>(type);
        for (int8_t i = 0; i < size; i++) {
            const char toPut = (qword >> (((size - 1) - i) * 8)) & 0xFF;
            stream.put(toPut);
        }
    }

    qword_t read(std::fstream& stream, const BlockType type) {
        const int8_t size = static_cast<int8_t>(type);
        qword_t out = 0;
        for (int8_t i = 0; i < size; i++) {
            int tmp = stream.get();
            if (tmp == std::char_traits<char>::eof()) throw std::exception();
            out |= tmp;
            out <<= (i * 8);
        }
        return out;
    }
}