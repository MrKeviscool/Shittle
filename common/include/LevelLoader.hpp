#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "FileStreamCommon.hpp"
#include "Level.hpp"

class LevelLoader {
public:
	void loadPack(const std::string& path);

	Level getLevel(const word_t index);
	std::vector<LevelThumbnail>& getThumbnails();

private:
	std::string packPath;
	std::fstream file;
	std::vector<LevelThumbnail> thumbnails;
};