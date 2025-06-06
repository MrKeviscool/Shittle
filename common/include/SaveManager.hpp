#pragma once

#include <vector>
#include <fstream>

#include "Level.hpp"

class SaveManager {
public:
    void loadPack(const std::string& path);
    void savePack(const std::string& path);
    void savePack();

    Level getLevelFromPack(const size_t index) const;
    const LevelThumbnail& getThumnails() const;
    void setLevelData(Level level, const size_t index);
    void setlevelThumbnail(const LevelThumbnail& thumbnail, size_t index);

private:
    std::fstream pack;

    std::vector<LevelThumbnail> m_thumbnails;
    std::vector<Level> levelsToSave;

    void loadLevel(const size_t index);
    void loadThumnails();

    std::string loadedPath;
};