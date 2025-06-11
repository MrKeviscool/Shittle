#include "LevelSaver.hpp"

qword_t getLevelSize(const Level& level){
    return
        sizeof(word_t) + //size of peg array
        level.pegs.size() * sizeof(PegInfo) + //array of pegs
        sizeof(dword_t) * 2 + //name pos + image size
        level.backgroundBytes.size(); //array of image bytes

}

qword_t getThumbSize(const LevelThumbnail& thumbnail){
    return
        sizeof(byte_t) + //level name length
        thumbnail.name.size() + //level name
        sizeof(dword_t) + //size of thumb image
        thumbnail.thumnailBytes.size();
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

void LevelSaver::saveLevel(const Level& level, const LevelThumbnail& thumbnail) {
    levelsToSave.emplace_back(level);
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
        curLevelOffset += static_cast<dword_t>(getLevelSize(lev));
    }
    return curLevelOffset;
}

dword_t LevelSaver::writeThumbnailOffsets(const dword_t firstThumbnailPos){
    dword_t curThumbOffset = firstThumbnailPos;
    for(auto& thumb : thumbnailsToSave){
        file::write(file, curThumbOffset, BlockType::dword);
        curThumbOffset += static_cast<dword_t>(getThumbSize(thumb));
    }
    return curThumbOffset;
}