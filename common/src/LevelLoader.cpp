#include "LevelLoader.hpp"

#include <fstream>

#include "FileStreamCommon.hpp"

static bool fileExists(const std::string& path){
    std::fstream file(path, std::ios::in);
    if(file.is_open()){
        file.close();
        return true;
    }
    return false;
}

void LevelLoader::loadPack(const std::string& path) {
    if (!fileExists(path)) throw std::exception();

    file.open(path);
    
    amountOfLevels = fileStream::read<byte_t>(file);
    loadLevelPositions();
    loadThumbnails();
}

void LevelLoader::closePack() {
    levelPositions.clear();
    thumbnails.clear();
    file.close();
}

const std::vector<LevelThumbnail>& LevelLoader::getThumbnails() {
    return thumbnails;
}

void LevelLoader::loadLevelPositions() {
    levelPositions.reserve(amountOfLevels);
    for (byte_t levOffsetIndex = 0; levOffsetIndex < amountOfLevels; levOffsetIndex++) {
        levelPositions.push_back(fileStream::read<dword_t>(file));
    }
}

void LevelLoader::loadThumbnails() {
    thumbnails.reserve(amountOfLevels);
    for (byte_t thumbIndex = 0; thumbIndex < amountOfLevels; thumbIndex++) {
        LevelThumbnail thumb;
        thumb.name = getThumbName();
        thumb.thumbnailBytes = getThumbImage();
        thumbnails.emplace_back(std::move(thumb));
    }
}

Level LevelLoader::getLevel(const byte_t index) {
    file.seekg(levelPositions[index]);
    
    Level level;
    level.pegs = getLevelPegs();
    level.backgroundBytes = getLevelImage();

    return level;

}

std::string LevelLoader::getThumbName() {
    const byte_t nameSize = fileStream::read<byte_t>(file);
    std::string name;
    name.reserve(nameSize);

    for (byte_t letterIndex = 0; letterIndex < nameSize; letterIndex++) {
        name.push_back(fileStream::read<byte_t>(file));
    }
    return name;
}

std::vector<byte_t> LevelLoader::getThumbImage() {
    const dword_t sizeOfImage = fileStream::read<dword_t>(file);
   
    std::vector<byte_t> imageBytes;
    imageBytes.reserve(sizeOfImage);

    for (dword_t imageByteIndex = 0; imageByteIndex < sizeOfImage; imageByteIndex++) {
        imageBytes.push_back(fileStream::read<byte_t>(file));
    }
    return imageBytes;

}

sf::Vector2f readVec2f(std::fstream& file) {
    return {
        dwordtoFloat(fileStream::read<dword_t>(file)),
        dwordtoFloat(fileStream::read<dword_t>(file)),
    };
}

std::vector<PegInfo> LevelLoader::getLevelPegs() {
    std::vector<PegInfo> pegs;
    pegs.resize(fileStream::read<word_t>(file));

    for (auto& peg : pegs) {
        peg.position = readVec2f(file);
        peg.size = readVec2f(file);
        peg.rotation = dwordtoFloat(fileStream::read<dword_t>(file));
        peg.shape = static_cast<PegShape>(fileStream::read<byte_t>(file));
    }
    return pegs;
}

std::vector<byte_t> LevelLoader::getLevelImage() {
    std::vector<byte_t> image;
    const dword_t imageSize = fileStream::read<dword_t>(file);
    image.reserve(imageSize);
    
    for (dword_t i = 0; i < imageSize; i++) {
        image.push_back(fileStream::read<byte_t>(file));
    }
    return image;
}
