#pragma once
#include <string>
#include <future>

std::string askForFileBlocking();
std::future<std::string> askForFileDeferred();
std::string askForSaveLocationBlocking();
std::future<std::string> askForSaveLocationDeferred();
