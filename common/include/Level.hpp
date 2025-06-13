#pragma once

#include <vector>
#include <string>

#include "PegInfo.hpp"
#include "FileStreamCommon.hpp"

struct LevelThumbnail {
    std::vector<byte_t> thumbnailBytes;
    std::string name;
};

struct Level {
    std::vector<PegInfo> pegs;
    std::vector<byte_t> backgroundBytes;
};


inline qword_t getLevelSize(const Level& level){
    return
        sizeof(word_t) + //size of peg array
        level.pegs.size() * sizeof(PegInfo) + //array of pegs
        sizeof(dword_t) * 2 + //name pos + image size
        level.backgroundBytes.size(); //array of image bytes

}

inline qword_t getThumbSize(const LevelThumbnail& thumbnail){
    return
        sizeof(byte_t) + //level name length
        thumbnail.name.size() + //level name
        sizeof(dword_t) + //size of thumb image
        thumbnail.thumbnailBytes.size();
}