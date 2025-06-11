#pragma once

#include <string>

#if defined(__linux__) || defined(macintosh) || defined(Macintosh) || defined(__APPLE__) && defined(__MACH__)
#define FS_POSIX
#elif defined(_WIN32)
#define FS_WINDOWS
#endif

#if !defined(FS_POSIX) && !defined(FS_WINDOWS)
#error unsupported OS
#endif

namespace fs{
    bool move(const std::string& oldName, const std::string& newName);
};