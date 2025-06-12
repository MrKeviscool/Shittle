#include "LevelSaver.hpp"

using levelAmount_t = byte_t;
using byteOffset_t = dword_t;

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
        thumbnail.thumbnailBytes.size();
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

static inline dword_t floatToDword(const float f) {
    return *reinterpret_cast<const dword_t*>(&f);
}

std::vector<byteOffset_t> getLevelOffsets(const std::vector<Level>& levels, const byteOffset_t startOffset){
    byteOffset_t curOffset = startOffset;
    std::vector<byteOffset_t> out;
    out.reserve(levels.size());

    for(auto& lev : levels){
        out.push_back(curOffset);
        curOffset += static_cast<byteOffset_t>(getLevelSize(lev));
    }
    return out;
}

std::vector<byteOffset_t> getThumbnailOffsets(const std::vector<LevelThumbnail>& thumbnails, const byteOffset_t startOffsert){
    byteOffset_t curOffset = startOffsert;
    std::vector<byteOffset_t> out;
    out.reserve(thumbnails.size());

    for(auto& thumb : thumbnails){
        out.push_back(curOffset);
        curOffset += static_cast<byteOffset_t>(getThumbSize(thumb));
    }
    return out;
}

void writePegInfo(std::fstream& file, const PegInfo& info){
    file::write(file, floatToDword(info.position.x), static_cast<BlockType>(sizeof(info.position.x))); //position
    file::write(file, floatToDword(info.position.y), static_cast<BlockType>(sizeof(info.position.y)));

    file::write(file, floatToDword(info.size.x), static_cast<BlockType>(sizeof(info.size.x))); //size
    file::write(file, floatToDword(info.size.y), static_cast<BlockType>(sizeof(info.size.y)));

    file::write(file, floatToDword(info.rotation), static_cast<BlockType>(sizeof(info.rotation))); //rotation

    file::write(file, static_cast<byte_t>(info.shape), BlockType::byte);

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
    
    headerSize = sizeof(levelAmount_t) + static_cast<dword_t>(levelsToSave.size()) * sizeof(dword_t) * 2;
    writeLevelAmount();

    std::vector<byteOffset_t> thumbOffsets = getThumbnailOffsets(thumbnailsToSave, headerSize);
    std::vector<byteOffset_t> levelOffsets = getLevelOffsets(levelsToSave, thumbOffsets.back() + static_cast<byteOffset_t>(getThumbSize(thumbnailsToSave.back())));
    
    writeOffsets(thumbOffsets);
    writeOffsets(levelOffsets);
    writeThumbnails();
    writeLevels();

    file.close();
}

void LevelSaver::writeLevelAmount(){
    file::write(file, levelsToSave.size(), static_cast<BlockType>(sizeof(levelAmount_t)));
}

void LevelSaver::writeOffsets(const std::vector<dword_t> &offsets){
    for(auto offset : offsets){
        file::write(file, offset, static_cast<BlockType>(sizeof(offset)));
    }
}

void LevelSaver::writeThumbnails(){
    for(auto& thumb : thumbnailsToSave){
        file::write(file, thumb.name.size(), BlockType::byte); //write name size
        for(char letter : thumb.name) file::write(file, letter, BlockType::byte); //write name
        file::write(file, thumb.thumbnailBytes.size(), BlockType::byte); //write image size
        for(byte_t byte : thumb.thumbnailBytes) file::write(file, byte, BlockType::byte); //write image
    }
}

void LevelSaver::writeLevels(){
    for(auto& lev : levelsToSave){
        file::write(file, lev.pegs.size(), BlockType::word);
        for(auto& peg : lev.pegs) writePegInfo(file, peg);
        file::write(file, lev.backgroundBytes.size(), BlockType::dword);
        for(auto byte : lev.backgroundBytes) file::write(file, byte, BlockType::byte);
    }
}
