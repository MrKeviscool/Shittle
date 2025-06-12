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