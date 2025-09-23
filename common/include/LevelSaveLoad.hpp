#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "SerializedData.hpp"

bool saveLevel(const std::string& path, const std::vector<SerializedLevelWrite>& levels);
std::pair<std::vector<SerializedLevelRead>, bool> loadLevels(const std::string& path);
