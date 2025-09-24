#pragma once

#include <string>
#include <vector>
#include <tuple>

#include "SerializedData.hpp"

bool saveSerializedLevels(const std::string& path, const std::vector<SerializedLevelWrite>& levels);
std::pair<std::vector<SerializedLevelRead>, bool> loadSerializedLevels(const std::string& path);
