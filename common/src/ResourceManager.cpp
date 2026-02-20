#include "ResourceManager.hpp"

void* ResourceManager::createResource(const std::string& path) {
	resources.emplace(path, path);
	return resources.at(path).resource;
}

void* ResourceManager::getResource(const std::string& path) {
	const auto foundResourceIter = resources.find(path);
	if (foundResourceIter == resources.end())
		return createResource(path);

	return foundResourceIter->second.resource;
}

void ResourceManager::createVirtualResource(void* resource, const std::string& path) {
	resources.emplace(path, Resource(resource, path));
}

void ResourceManager::unloadAll() {
    resources.clear();
}

void ResourceManager::unload(const std::string &path){
    resources.erase(path);   
}
