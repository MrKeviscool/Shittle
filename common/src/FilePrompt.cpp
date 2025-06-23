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
#error TODO
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
    text.setCharacterSize(nameTextHeight);

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
    sf::RenderWindow window(sf::VideoMode(originalSize.x, originalSize.y), "Pick File");
    

}

std::string askForFileBlocking(){
    sf::Vector2f originalSize{600.f, 600.f};
    sf::RenderWindow window(sf::VideoMode(originalSize.x, originalSize.y), "Pick File");
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
