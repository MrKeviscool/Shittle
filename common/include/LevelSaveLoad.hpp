#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "SerializedData.hpp"

bool saveLevel(const std::string& path, const std::vector<SerializedLevel>& levels);
std::pair<std::vector<SerializedLevel>, bool> loadLevels(const std::string& path);
