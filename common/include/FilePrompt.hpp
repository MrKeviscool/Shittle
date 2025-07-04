#pragma once
#include <string>
#include <functional>
#include <future>

void askForFileCallback(std::function<void(const std::string&)> callback);
std::string askForFileBlocking();
std::future<std::string> askForFileDefered();
