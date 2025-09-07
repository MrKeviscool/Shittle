#pragma once

#include <vector>
#include <string>

#include "SerializedData.hpp"
#include "FileStreamCommon.hpp"

struct LevelThumbnail {
    std::vector<byte_t> thumbnailBytes;
    std::string name;
};

struct Level {
    std::vector<SerializedPeg> pegs;
    std::vector<byte_t> backgroundBytes;
};


inline dword_t getLevelSize(const Level& level){
    return static_cast<dword_t>(
        sizeof(word_t) + //size of peg array
        level.pegs.size() * sizeof(SerializedPeg) + //array of pegs
        sizeof(dword_t) * 2 + //name pos + image size
        level.backgroundBytes.size()); //array of image bytes

}

inline dword_t getThumbSize(const LevelThumbnail& thumbnail){
    return static_cast<dword_t>(
        sizeof(byte_t) + //level name length
        thumbnail.name.size() + //level name
        sizeof(dword_t) + //size of thumb image
        thumbnail.thumbnailBytes.size());
}