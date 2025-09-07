#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "FileStreamCommon.hpp"
#include "Level.hpp"

class LevelLoader {
public:
	void loadPack(const std::string& path);
	void closePack();

	Level getLevel(const byte_t index);
	const std::vector<LevelThumbnail>& getThumbnails();

private:
	std::fstream file;
	std::vector<byteOffset_t> levelPositions;
	std::vector<LevelThumbnail> thumbnails;
	byte_t amountOfLevels;

	void loadLevelPositions();
	void loadThumbnails();

	std::string getThumbName();
	std::vector<byte_t> getThumbImage();

	std::vector<SerializedPeg> getLevelPegs();
	std::vector<byte_t> getLevelImage();
};