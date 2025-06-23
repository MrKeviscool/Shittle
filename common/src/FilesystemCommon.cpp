#include "FilesystemCommon.hpp"

#if defined(__linux__) || defined(macintosh) || defined(Macintosh) || defined(__APPLE__) && defined(__MACH__)
#define FS_POSIX
#elif defined(_WIN32)
#define FS_WINDOWS
#endif

#if !defined(FS_POSIX) && !defined(FS_WINDOWS)
#error unsupported OS
#endif


#if defined(FS_POSIX)
#include <stdio.h>
#elif defined(FS_WINDOWS)
#include <Windows.h>
#endif

namespace fs{
    bool move(const std::string& oldPath, const std::string& newPath){
        #ifdef FS_POSIX
        return !rename(oldPath.c_str(), newPath.c_str());
        #else
        return MoveFileA (
            oldPath.c_str(),
            newPath.c_str()
        );
        #endif
    }
};
