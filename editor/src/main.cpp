#include <SFML/Graphics.hpp>

#include <unordered_map>

#include "InputState.hpp"
#include "ResourceManager.hpp"
#include "Button.hpp"
#include "Peg.hpp"

#include "ButtonType.hpp"
#include "RunEditor.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Peg Edit", sf::Style::Default);
    window.setFramerateLimit(60);

    InputState::initalise(&window);
    InputState& input = InputState::getRef();
    ResourceManager resourceManger;

    std::unordered_map<ButtonType, Button> buttons = {
        {ButtonType::cursorPeg, Button(sf::Vector2f{50, 50}, sf::Vector2f{0, 0}, static_cast<sf::Texture*>(resourceManger.getResource("resources/pegButton.png")))},
        {ButtonType::cursorBrick, Button(sf::Vector2f{50, 50}, sf::Vector2f{50, 0}, static_cast<sf::Texture*>(resourceManger.getResource("resources/brickButton.png")))},
        {ButtonType::cursorSelect, Button(sf::Vector2f{50, 50}, sf::Vector2f{100, 0}, static_cast<sf::Texture*>(resourceManger.getResource("resources/jankyCursor.png")))},
    };

    const sf::Font* textFont = static_cast<const sf::Font*>(resourceManger.getResource("resources/robotto.ttf"));
    buttons[ButtonType::cursorPeg].setText("peg", textFont, 15U, 0.0f);
    buttons[ButtonType::cursorBrick].setText("brick", textFont, 15U, 0.0f);
    buttons[ButtonType::cursorSelect].setText("select", textFont, 15U, 0.0f);
    
    runEditor(window, input, resourceManger, buttons);
}