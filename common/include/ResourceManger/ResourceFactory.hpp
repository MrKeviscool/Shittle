#pragma once

#include <string>
#include <memory>

#include "ResourceManger/Resource.hpp"


std::unique_ptr<Resource> ResourceFactory(const std::string& path);