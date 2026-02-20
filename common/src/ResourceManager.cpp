#include "ResourceManager.hpp"

void ResourceManager::unloadAll() {
    resources.clear();
}

void ResourceManager::unload(const std::string &path){
    resources.erase(path);   
}

std::unique_ptr<BinaryBlobVec> ResourceManager::loadResourceBin(const std::string& path) {
	std::ifstream fileStream(path, std::ios::binary | std::ios::in | std::ios::ate);

	if (!fileStream.is_open()) return nullptr;

	const auto fileSize = fileStream.tellg();
	auto fileData = std::make_unique<BinaryBlobVec>(static_cast<size_t>(fileSize));

	fileStream.read(reinterpret_cast<char*>(fileData->data()), fileSize);
	return fileData;
}
