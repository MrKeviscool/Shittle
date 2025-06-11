#include "LevelSaver.hpp"

qword_t getLevelSize(const Level& level){
    return
        sizeof(word_t) + 
        level.pegs.size() * sizeof(PegInfo) +
        sizeof(byte_t) +
        level.name.size() +
        sizeof(dword_t) +
        level.backgroundBytes.size();
}

qword_t getThumbSize(const LevelThumbnail& thumbnail){
    return 
        sizeof(dword_t) * 2 + //because of name pointer and img size
        sizeof(thumbnail.thumnailBytes.size());
}

bool fileExists(const std::string& path){
    std::fstream file(path, std::ios::in);
    if(file.is_open()){
        file.close();
        return true;
    }
    return false;
}

bool hasWriteAccess(const std::string& path){
    std::fstream file(path, std::ios::in | std::ios::out);
    if(file.is_open()){
        file.close();
        return true;
    }
    file.open(path, std::ios::out);
    if(file.is_open()){
        file.close();
        return true;
    }
    return false;
}

void LevelSaver::saveLevel(const Level& level){
    levelsToSave.emplace_back(level);
}

void LevelSaver::saveLevel(Level&& level){
    levelsToSave.emplace_back(level);
}

void LevelSaver::saveThumbnail(const int index, const std::string imagePath){
    LevelThumbnail thumbnail{std::vector<char>{}, levelsToSave.at(index)};

    thumbnailsToSave.emplace_back(thumbnail);
}

void LevelSaver::writeToDisk(const std::string &filePath)
{
    path = filePath;
    if(!hasWriteAccess(filePath)){
        throw std::exception();
    }
    
    file.open(path, std::ios::out);
    if(!file.is_open()) throw std::exception();
    
    headerSize = sizeof(word_t) + levelsToSave.size() * sizeof(dword_t) * 2;
    writeLevelAmount();
    const dword_t thumbnailOffset = writeLevelOffsets(2);
    writeThumbnailOffsets(thumbnailOffset);
}

void LevelSaver::writeLevelAmount(){
    file::write(file, levelsToSave.size(), BlockType::word);
}


dword_t LevelSaver::writeLevelOffsets(const dword_t firstLevelPos){
    dword_t curLevelOffset = firstLevelPos;
    for(auto& lev : levelsToSave){
        file::write(file, curLevelOffset, BlockType::dword);
        curLevelOffset += getLevelSize(lev);
    }
    return curLevelOffset;
}

dword_t LevelSaver::writeThumbnailOffsets(const dword_t firstThumbnailPos){
    dword_t curThumbOffset = firstThumbnailPos;
    for(auto& thumb : thumbnailsToSave){
        file::write(file, curThumbOffset, BlockType::dword);
        curThumbOffset += getThumbSize(thumb);
    }
    return curThumbOffset;
}