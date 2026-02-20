#pragma once

#include <string>

enum class ResourceManagerResourceType : uint8_t;
struct  ResourceManagerResource;

using Resource = ResourceManagerResource;
using ResourceType = ResourceManagerResourceType;

enum class ResourceManagerResourceType : uint8_t {
	Void,
	Image,
	Font,
	Texture,
};

struct  ResourceManagerResource {
	ResourceType resourceType;
	void* resource;
	
	ResourceManagerResource& operator=(ResourceManagerResource&&) noexcept;

	ResourceManagerResource(ResourceManagerResource&&) noexcept;
	ResourceManagerResource(void* resource, ResourceType fileType);
	ResourceManagerResource(void* resource, const std::string& path);
	ResourceManagerResource(const std::string& path);
	~ResourceManagerResource();
};
