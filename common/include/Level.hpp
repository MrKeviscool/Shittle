#pragma once

#include <vector>
#include <string>

#include "PegInfo.hpp"

struct LevelThumbnail {
    std::vector<char> thumnailBytes;
    std::string name;
};

struct Level {
    std::vector<PegInfo> pegs;
    std::vector<char> backgroundBytes;
    std::string name;
};