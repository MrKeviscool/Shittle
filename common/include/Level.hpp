#pragma once

#include <vector>
#include <string>

#include "PegInfo.hpp"

struct Level {
    std::vector<PegInfo> pegs;
    std::vector<char> backgroundBytes;
    std::string name;
};

struct LevelThumbnail {
    std::vector<char> thumnailBytes;
    std::reference_wrapper<const Level> refferingLevel;
};