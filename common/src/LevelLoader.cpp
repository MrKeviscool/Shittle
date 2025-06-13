//TODO
#if 0
#include <fstream>

static bool fileExists(const std::string& path){
    std::fstream file(path, std::ios::in);
    if(file.is_open()){
        file.close();
        return true;
    }
    return false;
}
#endif