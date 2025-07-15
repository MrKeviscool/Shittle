#pragma once
#include <string>
#include <future>

std::string askForFileBlocking();
std::future<std::string> askForFileDefered();
