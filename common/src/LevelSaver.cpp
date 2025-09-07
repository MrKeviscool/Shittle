#include "LevelSaver.hpp"

using levelAmount_t = byte_t;

dword_t LevelSaver::getTotalThumbnailsSize(){
    byteOffset_t size = 0;
    for(auto& thumb : thumbnailsToSave){
        size += getThumbSize(thumb);
    }
    return size;
}

void LevelSaver::writePegInfo(const SerializedPeg& info){
    fileStream::write(file, floatToDword(info.position.x), static_cast<BlockType>(sizeof(info.position.x))); //position
    fileStream::write(file, floatToDword(info.position.y), static_cast<BlockType>(sizeof(info.position.y)));

    fileStream::write(file, floatToDword(info.size.x), static_cast<BlockType>(sizeof(info.size.x))); //size
    fileStream::write(file, floatToDword(info.size.y), static_cast<BlockType>(sizeof(info.size.y)));

    fileStream::write(file, floatToDword(info.rotation), static_cast<BlockType>(sizeof(info.rotation))); //rotation

    fileStream::write(file, static_cast<byte_t>(info.shape), BlockType::byte);

}

void LevelSaver::saveLevel(const Level& level, const LevelThumbnail& thumbnail) {
    levelsToSave.emplace_back(level);
    thumbnailsToSave.emplace_back(thumbnail);
}

void LevelSaver::writeLevelAmount(){
    fileStream::write(file, levelsToSave.size(), static_cast<BlockType>(sizeof(levelAmount_t)));
}

void LevelSaver::writeLevelOffsets(const byteOffset_t initalOffset){
    byteOffset_t curOffset = initalOffset;
    for(auto& lev : levelsToSave){
        fileStream::write(file, curOffset, static_cast<BlockType>(sizeof(curOffset)));
        curOffset += getLevelSize(lev);
    }
}

void LevelSaver::writeThumbnails(){
    for(auto& thumb : thumbnailsToSave){
        fileStream::write(file, thumb.name.size(), BlockType::byte); //write name size
        for(char letter : thumb.name) fileStream::write(file, letter, BlockType::byte); //write name
        fileStream::write(file, thumb.thumbnailBytes.size(), BlockType::dword); //write image size
        for(byte_t byte : thumb.thumbnailBytes) fileStream::write(file, byte, BlockType::byte); //write image
    }
}

void LevelSaver::writeLevels(){
    for(auto& lev : levelsToSave){
        fileStream::write(file, lev.pegs.size(), BlockType::word);
        for(auto& peg : lev.pegs) writePegInfo(peg);
        fileStream::write(file, lev.backgroundBytes.size(), BlockType::dword);
        for(auto byte : lev.backgroundBytes) fileStream::write(file, byte, BlockType::byte);
    }
}

void LevelSaver::writeToDisk(const std::string &filePath)
{
    path = filePath;
    if(!fileStream::hasWriteAccess(filePath)){
        throw std::exception();
    }
    
    file.open(path, std::ios::out);
    if(!file.is_open()) throw std::exception();
    
    headerSize = sizeof(levelAmount_t) + static_cast<word_t>(levelsToSave.size()) * sizeof(byteOffset_t); //size of level offset byte array + amount of levels byte

    writeLevelAmount();
    writeLevelOffsets(headerSize + getTotalThumbnailsSize());
    writeThumbnails();
    writeLevels();
    
    file.close();
}