#include "ResourceManager.hpp"

#include "ResourceManger/ResourceFactory.hpp"

ResourceManager ResourceManager::m_manager;



ResourceManager* ResourceManager::getPtr(){
    return &m_manager;
}

ResourceManager& ResourceManager::getRef(){
    return m_manager;
}



Resource* ResourceManager::getResource(std::string& path){
    if(resources.find(path) == resources.end()){
        resources.emplace(path, ResourceFactory(path));
    }
    
    return resources[path].get();

}