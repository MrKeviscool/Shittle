#include "FilePrompt.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <sys/types.h>
#include <utility>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "InputState.hpp"
#include "ResourceManager.hpp"

#if defined(__linux__) || defined(macintosh) || defined(Macintosh) || defined(__APPLE__) && defined(__MACH__)
#define FP_POSIX
#elif defined(_WIN32)
#define FP_WINDOWS
#else
#error unsupported OS
#endif

#if defined(FP_POSIX)
#include <dirent.h>
#elif defined(FP_WINDOWS)
#include <Windows.h>
#endif

static bool isDirectory(const std::string& path);
static std::vector<std::string> getFilesIn(const std::string& path);

#ifdef FP_POSIX

static bool isDirectory(const std::string& path){
    DIR* dir = opendir(path.c_str());
    bool out;
    if(errno == ENOTDIR) out = false;
    else out = true;
    closedir(dir);
    return out;
}

static std::vector<std::string> getFilesIn(const std::string& path){
    std::vector<std::string> out;
    DIR* dir = opendir(path.c_str());
    if(!dir) return {};
    
    while(const dirent* file = readdir(dir)){
        out.push_back(file->d_name);
    }

    closedir(dir);
    return out;
}
#else //WINDOWS
static bool isDirectory(const std::string& path) {
    HANDLE fdHandle = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    bool out;
    if (fdHandle == INVALID_HANDLE_VALUE) {
        out = false;
    }
    else {
        out = true;
    }
    CloseHandle(fdHandle);
    return out;
}

static std::vector<std::string> getFilesIn(const std::string& path) {
#error does not currently work
    std::vector<std::string> out;
    SetCurrentDirectoryA(path.c_str());
    WIN32_FIND_DATAA fileInfo;

    HANDLE fdHandle = FindFirstFileA("*", &fileInfo);
    if (!fdHandle) return {};

    char pathBuff[MAX_PATH];

    do {
        GetFinalPathNameByHandleA(fdHandle, pathBuff, MAX_PATH - 1, FILE_NAME_OPENED | VOLUME_NAME_NONE);
        out.push_back({ pathBuff });
    } while (FindNextFileA(fdHandle, &fileInfo));
    return out;
}

#endif

static void sortFiles(std::vector<std::string>& files){


}

static void displayFiles(sf::RenderWindow& window, std::vector<std::string> files, const sf::Font& font, float topOffset = 10.f, float nameTextHeight = 10.f){
    bool bright = true;

    const sf::Color brightColor{127, 127, 127};
    const sf::Color darkColor{static_cast<uint8_t>(127*0.7f), static_cast<uint8_t>(127*0.7f), static_cast<uint8_t>(127*0.7f)};
    sf::RectangleShape bgRect({600, nameTextHeight});
    bgRect.setFillColor((bright? brightColor : darkColor));
    bgRect.setPosition(0, topOffset);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(static_cast<unsigned int>(nameTextHeight));

    text.setPosition(0, topOffset);

    auto changeBgColor = [&bgRect, &bright, &brightColor, &darkColor](){
        bright = !bright;
        bgRect.setFillColor((bright? brightColor : darkColor));
    };

    for(auto& file : files){
        text.setString(file);
        window.draw(bgRect);
        window.draw(text);

        bgRect.move(0, nameTextHeight);
        text.move(0, nameTextHeight);
        changeBgColor();
    }
}

void askForFileDefered(std::function<void (const std::string &)> callback){
    sf::Vector2f originalSize{600.f, 600.f};
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(originalSize.x), static_cast<unsigned int>(originalSize.y)), "Pick File");
    

}

std::string askForFileBlocking(){
    sf::Vector2f originalSize{600.f, 600.f};
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(originalSize.x), static_cast<unsigned int>(originalSize.y)), "Pick File");
    InputState::initalise(&window);
    InputState& input = InputState::getRef();
    
    ResourceManager resources;
    sf::Font* textFont = static_cast<sf::Font*>(resources.getResource("resources/robotto.ttf"));

    auto files = getFilesIn(".");

    while(window.isOpen()){
        input.pollEvents();
        window.clear();
        displayFiles(window, files, *textFont);
        window.display();
        const InputState::KeyInfo escSequence = {sf::Keyboard::Key::Escape, InputState::ButtonState::released};
        if(input.keyEvents().find(escSequence) != input.keyEvents().end()){
            window.close();
        }
    }

    return "";
}
