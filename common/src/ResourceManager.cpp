#include "ResourceManager.hpp"

#include "ResourceManger/ResourceFactory.hpp"

void* ResourceManager::getResource(const std::string& path){
    if(resources.find(path) == resources.end()){
        resources.emplace(path, ResourceFactory(path));
    }
    
    return resources[path].get()->getResource();

}

void ResourceManager::unloadAll() {
    resources.clear();
}

void ResourceManager::unload(const std::string &path){
    resources.erase(path);   
}