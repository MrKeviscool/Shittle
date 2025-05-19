#include <SFML/Graphics.hpp>

#include <unordered_map>

#include "InputState.hpp"
#include "ResourceManager.hpp"
#include "Button.hpp"
#include "Peg.hpp"

#include "RunEditor.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Peg Edit", sf::Style::Default);
    window.setFramerateLimit(60);

    InputState::initalise(&window);
    InputState& input = InputState::getRef();
    ResourceManager resourceManger;

    std::unordered_map<std::string, Button> buttons = {
        {"cursorPeg", Button(sf::Vector2f{50, 50}, sf::Vector2f{0, 0}, static_cast<sf::Texture*>(resourceManger.getResource("resources/pegButton.png")))},
        {"cursorBrick", Button(sf::Vector2f{50, 50}, sf::Vector2f{50, 0}, static_cast<sf::Texture*>(resourceManger.getResource("resources/brickButton.png")))},
        {"cursorSelect", Button(sf::Vector2f{50, 50}, sf::Vector2f{100, 0}, static_cast<sf::Texture*>(resourceManger.getResource("resources/jankyCursor.png")))},
    };
    
    const sf::Font* textFont = static_cast<const sf::Font*>(resourceManger.getResource("resources/robotto.ttf"));
    buttons["cursorPeg"].setText("peg", textFont, 15U, 0.0f);
    buttons["cursorBrick"].setText("brick", textFont, 15U, 0.0f);
    buttons["cursorSelect"].setText("select", textFont, 15U, 0.0f);
    
    runEditor(window, input, resourceManger, buttons);
}