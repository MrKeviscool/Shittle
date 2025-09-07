#pragma once

#include <string>
#include <vector>

#include "Level.hpp"
#include "FileStreamCommon.hpp"

class LevelSaver {
public:
    void saveLevel(const Level& level, const LevelThumbnail& thumbnail);

    void writeToDisk(const std::string& filePath);
private:
    std::fstream file;
    std::string path;
    word_t headerSize = 0;
    std::vector<Level> levelsToSave;
    std::vector<LevelThumbnail> thumbnailsToSave;

    void writeLevelAmount();
    void writeLevelOffsets(const dword_t initalOffset);

    void writeLevels();
    void writeThumbnails();

    void writePegInfo(const SerializedPeg& peg);
    dword_t getTotalThumbnailsSize();
};
