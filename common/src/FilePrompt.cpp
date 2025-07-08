#include "FilePrompt.hpp"

#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include "InputState.hpp"
#include "ResourceManager.hpp"
#include "TextField.hpp"
#include "MulColor.hpp"

#if defined(__linux__) || defined(macintosh) || defined(Macintosh) || defined(__APPLE__) && defined(__MACH__)
#define FP_POSIX
#elif defined(_WIN32)
#define FP_WINDOWS
#else
#error unsupported OS
#endif

#if defined(FP_POSIX)
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#elif defined(FP_WINDOWS)
#include <Windows.h>
#endif

enum class OpenMode {
    files,
    directories
};

static bool isDirectory(const std::string& path){
#ifdef FP_POSIX
    DIR* dir = opendir(path.c_str());
    bool out;
    if(errno == ENOTDIR) out = false;
    else out = true;
    closedir(dir);
    return out;
#else
    const DWORD fileAttr = GetFileAttributesA(path.c_str());
    return fileAttr & FILE_ATTRIBUTE_DIRECTORY;
#endif
}

static bool isHidden(const std::string& path){
#ifdef FP_POSIX
    return path[0] == '.';
#else
    const DWORD fileAttr = GetFileAttributesA(path.c_str());
    return fileAttr & FILE_ATTRIBUTE_HIDDEN;
#endif

}

static std::vector<std::string> getFilesIn(const std::string& path){
#ifdef FP_POSIX
    std::vector<std::string> out;
    DIR* dir = opendir(path.c_str());
    if(!dir) return {};
    
    while(const dirent* file = readdir(dir)){
        std::string fileName = file->d_name;
        if(isDirectory(fileName)) fileName.push_back('/');
        out.emplace_back(std::move(fileName));
    }

    closedir(dir);
    return out;
#else

    std::vector<std::string> out;
    SetCurrentDirectoryA(path.c_str());
    
    WIN32_FIND_DATAA fileInfo;
    HANDLE fdHandle = FindFirstFileA(".\\*", &fileInfo);
    if (fdHandle == INVALID_HANDLE_VALUE) return {};
    do {
        out.emplace_back(fileInfo.cFileName);
        if(isDirectory(out.back())) out.back().push_back('/');
    } while (FindNextFileA(fdHandle, &fileInfo));
    FindClose(fdHandle);
    return out;
#endif
}

static std::vector<std::string> sortNames(const std::vector<std::string>& names){
    std::vector<std::string> files;
    std::vector<std::string> directories;

    for(auto& name : names){
        if(name.back() == '/')
            directories.push_back(name);
        else
            files.push_back(name);
    }
    
    std::sort(files.begin(), files.end());
    std::sort(directories.begin(), directories.end());

    std::vector<std::string> out;
    out.reserve(files.size() + directories.size());
    out.insert(out.cend(), directories.begin(), directories.end());
    out.insert(out.cend(), files.begin(), files.end());
    return out;
}

struct DisplaySettings {
    float nameBlockSize = 10.f;
    float topOffset = 10.f;
    bool displayHidden = false;
};

static void displayFiles(sf::RenderWindow& window, std::vector<std::string> files, const sf::Font& font, const DisplaySettings& settings){
    const sf::Color brightColor{127, 127, 127};
    const MulColor darkColor(brightColor, 0.7f);
    sf::RectangleShape bgRect({600, settings.nameBlockSize});
    bgRect.setFillColor(brightColor);
    bgRect.setPosition(0, settings.topOffset);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(static_cast<unsigned int>(settings.nameBlockSize));

    text.setPosition(0, settings.topOffset);
    text.move(0, text.getCharacterSize() * -0.25f);
    
    bool bright = true;
    auto changeBgColor = [&bright, &bgRect, &brightColor, &darkColor]() mutable {
        bright = !bright;
        bgRect.setFillColor((bright? brightColor : darkColor));
    };

    for(auto& file : files){
        if(!settings.displayHidden && isHidden(file)) continue;
        text.setString(file);
        window.draw(bgRect);
        window.draw(text);

        bgRect.move(0, settings.nameBlockSize);
        text.move(0, settings.nameBlockSize);
        changeBgColor();
    }
}

static std::string getHoveredName(const InputState& input, const std::vector<std::string>& files, const DisplaySettings& displaySettings){
    const sf::Vector2i mousePos = input.mousePos();
    const unsigned int clickIndex = (mousePos.y - static_cast<unsigned int>(displaySettings.topOffset)) / static_cast<unsigned int>(displaySettings.nameBlockSize);

    if(clickIndex >= files.size() || mousePos.y < displaySettings.topOffset) return "";
    
    if(displaySettings.displayHidden) return files[clickIndex];

    if(std::count_if(files.cbegin(), files.cend(), [](const std::string& fn){return !isHidden(fn);}) <= clickIndex) return ""; //hopefully can remove this and do checking in loop

    auto nameIter = files.cbegin();
    unsigned int visibleBlockIndex = 0;
    while(visibleBlockIndex < clickIndex) {
        do nameIter++; while(isHidden(*nameIter) && nameIter != files.cend());
        if(nameIter == files.cend()) return "";
        visibleBlockIndex++;
    } 

    return *nameIter;
}


static std::string relToAbsPath(const std::string& rel){
#ifdef FP_POSIX
    char* absPathPtr = realpath(rel.c_str(), NULL);
    std::string absPath(absPathPtr);
    free(absPathPtr);
    return absPath;
#else
    char strBuffer[MAX_PATH + 1];
    GetFullPathNameA(rel.c_str(), MAX_PATH, strBuffer, NULL);
    return strBuffer;
#endif
}

static bool exitCheck(const InputState& input){
    return input.keyEventsContains({sf::Keyboard::Escape, InputState::ButtonState::pressed});
}
static std::string getClickedName(const InputState& input, const std::vector<std::string>& files, const DisplaySettings& displaySettings, TextField& nameField){
    if(input.mouseEventsContains({sf::Mouse::Button::Left, InputState::ButtonState::pressed})){
        std::string clickedName = getHoveredName(input, files, displaySettings);
        if(!clickedName.empty()){ //clicked on file
            nameField.setEnteredText(std::move(clickedName));
            if(input.doubleClicked()){
                nameField.submitEntered();
                return nameField.enteredText();
            }
        }
    }
    return "";
}

static void changeDirectory(const std::string& dir) {
#ifdef FP_POSIX
    chdir(dir.c_str());
#else // FP_POSIX
    SetCurrentDirectoryA(dir.c_str());
#endif
}

static std::string askForFile(){
    sf::Vector2f originalSize{600.f, 600.f};
    sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int>(originalSize.x), static_cast<unsigned int>(originalSize.y)), "Pick File");
    window.setFramerateLimit(60);

    std::string originalPath = relToAbsPath(".");

    InputState::initalise(&window);
    InputState& input = InputState::getRef();
    
    ResourceManager resources;
    sf::Font* textFont = static_cast<sf::Font*>(resources.getResource("resources/robotto.ttf"));

    TextField pathField(input, *textFont, "");
    TextField nameField(input, *textFont, "file name:");

    pathField.setSize({600.f, 20.f});
    nameField.setSize({600.f, 20.f});

    pathField.setPosition({0.f, 0.f});
    nameField.setPosition({0.f, 600.f - 20.f});

    pathField.setBgColor({128/2, 128/2, 128/2});
    nameField.setBgColor({128/2, 128/2, 128/2});

    pathField.setSelectedBrightnessMult(1.4f);
    nameField.setSelectedBrightnessMult(1.4f);

    std::vector<std::string> files = getFilesIn(".");
    files = sortNames(files);

    pathField.setEnteredText(relToAbsPath("."));
   
    DisplaySettings displaySettings;
    displaySettings.nameBlockSize = 20.f;
    displaySettings.displayHidden = false;
    displaySettings.topOffset = 20.f;


    while(window.isOpen()){
        input.pollEvents();

        const std::string doubleClickedName = getClickedName(input, files, displaySettings, nameField);
        if (!doubleClickedName.empty() && isDirectory(doubleClickedName)) {
            changeDirectory(doubleClickedName);
            pathField.setEnteredText(relToAbsPath("."));
            files = getFilesIn(".");
            continue;
        }

        pathField.poll();
        nameField.poll();
        window.clear();
        displayFiles(window, files, *textFont, displaySettings);
        pathField.display(window);
        nameField.display(window);
        window.display();
        if(exitCheck(input) || input.shouldClose())
            window.close();
        
    }
    changeDirectory(originalPath);
    return "";
}

std::future<std::string> askForFileDefered(){
    std::packaged_task<std::string()> task(askForFile);
    auto future = task.get_future();
    std::thread thread(std::move(task));
    thread.detach();
    return future;
}

std::string askForFileBlocking(){
    return askForFile();
}

/*bug with clicking the correct entry across windows and linux*/
