#pragma once

#include <string>
#include <vector>

#include "Level.hpp"
#include "FileStreamCommon.hpp"

class LevelSaver {
public:
    void saveLevel(const Level& level, const LevelThumbnail& thumbnail);
    //void saveLevel(Level&& level, LevelThumbnail&& thumbnail);

    void writeToDisk(const std::string& filePath);

private:
    std::fstream file;
    std::string path;
    qword_t headerSize = 0;
    std::vector<Level> levelsToSave;
    std::vector<LevelThumbnail> thumbnailsToSave;

    void writeLevelAmount();

    //returns the first avaliable offset after levels
    dword_t writeLevelOffsets(const dword_t firstLevelPos);
    
    //returns the first avaliable offset after thumbnails
    dword_t writeThumbnailOffsets(const dword_t firstThumbPos);

    void writeLevels();
    void writeThumbnails();
};