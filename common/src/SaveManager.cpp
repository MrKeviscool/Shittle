#include "SaveManager.hpp"

#include <cstddef>

enum class BlockType{
    byte = 1,
    word = 2,
    dword = 4,
    qword = 8
};

void write(std::fstream& stream, const int64_t qword, const BlockType type){
    const int8_t size = static_cast<int8_t>(type);
    for(int8_t i = 0; i < size; i++){
        const char toPut = (qword >> (((size - 1) - i) * 8)) & 0xFF;
        stream.put(toPut);
    }
}

int64_t read(std::fstream& stream, const BlockType type){
    return 0;
}

void SaveManager::loadPack(const std::string& path){
    pack.open(path, std::ios::in);
    if(!pack.is_open()) throw std::exception();
    loadedPath = path;
}

void SaveManager::savePack(const std::string& path){
    if(pack.is_open()) pack.close();
    pack.open(path, std::ios::in | std::ios::out); //opens for write but does not clear file
    if(!pack.is_open()){
        pack.open(path, std::ios::out);
        if(!pack.is_open()) throw std::exception();
    }

    write(pack, 0b0101010111111111, BlockType::word);
    pack.flush();
    pack.close();
}

void SaveManager::savePack(){
    savePack(loadedPath);
}

Level SaveManager::getLevelFromPack(const size_t index) const {
    return Level{
        .pegs{},
        .backgroundBytes{},
        .name{},
    };
}

void SaveManager::setLevelData(Level level, const size_t index){

}