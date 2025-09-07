#pragma once

#include <string>
#include <vector>
#include <tuple>

#include <SFML/System/Vector2.hpp>

#include "FileStreamCommon.hpp"
#include "SerializedData.hpp"

enum class LevelSaveError : char {
	None,
	Permissions,
	Other,
};

enum class LevelLoadError : char {
	None,
	Permissions,
	Missing,
	Corrupted,
	Other,
};

LevelSaveError saveLevel(const std::vector<SerializedLevel>& levels);

std::pair<std::vector<SerializedLevel>, LevelLoadError>
loadLevels(const std::string& path);
