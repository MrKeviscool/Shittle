#include "ResourceManger/ResourceFactory.hpp"

#include "ResourceManger/ImageResource.hpp"

#include <stdexcept>

//could use a string view here
std::string getFileTypeStr(const std::string& path){
    std::string fileTypeBuff;
    for(auto iter = path.crend() + 1; iter != path.crbegin()+1; iter++)
    if(*iter != '.')
        fileTypeBuff.push_back(*iter);
    else
        break;
    return fileTypeBuff;
}

std::unique_ptr<Resource> ResourceFactory(const std::string& path){

    std::string fileTypeBuff = getFileTypeStr(path);
    
    if(fileTypeBuff.size() == path.size()) throw std::exception();
    
    if(fileTypeBuff == ".png"
        | fileTypeBuff == ".jpg")
        return std::unique_ptr<Resource>(new ImageResource(path));
    
    else throw std::runtime_error("error loading extention");
};