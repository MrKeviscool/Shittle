#pragma once
#include <string>
#include <functional>

void askForFileDefered(std::function<void(const std::string&)> callback);
std::string askForFileBlocking();
