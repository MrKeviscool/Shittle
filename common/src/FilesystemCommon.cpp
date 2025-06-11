#include "FilesystemCommon.hpp"

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
        return MoveFile (
            const_cast<char*>(oldPath.c_str()),
            const_cast<char*>(newPath.c_str())
        );
        #endif
    }
};