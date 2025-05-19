#pragma once

#include <string>
#include <memory>

class Resource;


std::unique_ptr<Resource> ResourceFactory(const std::string& path);