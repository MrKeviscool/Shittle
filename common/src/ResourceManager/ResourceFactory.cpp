#include "ResourceManger/ResourceFactory.hpp"

#include "ResourceManger/ImageResource.hpp"
#include "ResourceManger/FontResource.hpp"

#include <stdexcept>

//could use a string view here
std::string getFileTypeStr(const std::string& path){

    std::uint8_t extentionSize = 0;

    for (auto iter = path.crbegin(); iter != path.crend(); iter++)
        if (*iter != '.')
            extentionSize++;
    else
        break;

    std::string fileTypeBuff;
    fileTypeBuff.reserve(extentionSize);

    for (std::uint8_t i = path.size() - extentionSize; i < path.size(); i++)
        fileTypeBuff.push_back(path[i]);
    

    return fileTypeBuff;
}

std::unique_ptr<Resource> ResourceFactory(const std::string& path){

    std::string fileTypeBuff = getFileTypeStr(path);
    
    if(fileTypeBuff.size() == path.size()) throw std::exception();
    
    if(fileTypeBuff == "png"
        || fileTypeBuff == "jpg")
        return std::unique_ptr<Resource>(new ImageResource(path));
    
    if(fileTypeBuff == "ttf")
        return std::unique_ptr<Resource>(new FontResource(path));

    else throw std::runtime_error("error loading extention");
};