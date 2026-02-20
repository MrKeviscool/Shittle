//#include <cassert>
//#include <stdexcept>
//
//#include "ResourceManagerResource.hpp"
//
//#include <SFML/Graphics/Image.hpp>
//#include <SFML/Graphics/Font.hpp>
//
//static std::string getFileTypeStr(const std::string& path){
//
//	std::uint8_t extentionSize = 0;
//
//	for (auto iter = path.crbegin(); iter != path.crend(); iter++)
//	if (*iter != '.')
//		extentionSize++;
//	else
//		break;
//
//	std::string fileTypeBuff;
//	fileTypeBuff.reserve(extentionSize);
//
//	for (std::uint8_t i = static_cast<uint8_t>(path.size()) - extentionSize; i < path.size(); i++)
//		fileTypeBuff.push_back(path[i]);
//
//	return fileTypeBuff;
//}
//
//static ResourceType fileExtentionToType(const std::string& fileExtention){
//	if (fileExtention == "png"
//		|| fileExtention == "jpg"
//		|| fileExtention == "jpeg")
//	{
//		return ResourceType::Image;
//	}
//	if (fileExtention == "ttf") {
//		return ResourceType::Font;
//	}
//	if (fileExtention == "tex") {
//		return ResourceType::Texture;
//	}
//	else throw std::runtime_error("do not support type" + fileExtention);
//}
//
//ResourceManagerResource::ResourceManagerResource(ResourceManagerResource&& other) noexcept {
//	this->resourceType = other.resourceType;
//	other.resourceType = ResourceType::Void;
//
//	this->resource = other.resource;
//	other.resource = nullptr;
//}
//
//ResourceManagerResource& ResourceManagerResource::operator=(ResourceManagerResource&& other) noexcept {
//	this->resourceType = other.resourceType;
//	other.resourceType = ResourceType::Void;
//
//	this->resource = other.resource;
//	other.resource = nullptr;
//	return *this;
//}
//
//ResourceManagerResource::ResourceManagerResource
//	(void* resource, ResourceType fileType) : resource(resource), resourceType(fileType)
//{
//
//}
//
//
//ResourceManagerResource::ResourceManagerResource(void* resource, const std::string& path) : resource(resource) {
//	resourceType = fileExtentionToType(getFileTypeStr(path));
//}
//
//ResourceManagerResource::ResourceManagerResource(const std::string& path){
//	resourceType = fileExtentionToType(getFileTypeStr(path));
//
//	switch (resourceType) {
//	case ResourceType::Image:
//		resource = new sf::Image;
//		static_cast<sf::Image*>(resource)->loadFromFile(path);
//		break;
//	case ResourceType::Font:
//		resource = new sf::Font;
//		static_cast<sf::Font*>(resource)->loadFromFile(path);
//		break;
//	default:
//		throw std::runtime_error("error proccessing file type");
//	}
//
//}
//
//ResourceManagerResource::~ResourceManagerResource() {
//	switch (resourceType) {
//	case ResourceType::Void:
//		break;
//	case ResourceType::Image:
//		delete static_cast<sf::Image*>(resource);
//		break;
//	case ResourceType::Font:
//		delete static_cast<sf::Font*>(resource);
//		break;
//	case ResourceType::Texture:
//		delete static_cast<sf::Texture*>(resource);
//		break;
//	default:
//		assert(false);
//	}
//}
