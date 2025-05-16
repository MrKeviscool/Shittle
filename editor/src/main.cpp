#include <SFML/Graphics.hpp>

#include "InputState.hpp"
#include "ResourceManager.hpp"
#include "Button.hpp"
#include "Peg.hpp"


int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Peg Edit", sf::Style::Default);
    window.setFramerateLimit(60);

    InputState::initalise(&window);
    InputState& input = InputState::getRef();
    ResourceManager resourceManger;

    std::vector<Button> buttons = {
        Button(sf::Vector2f{50, 50}, sf::Vector2f{1920-50, 0}, static_cast<sf::Texture*>(resourceManger.getResource("resources/extIco.png")), [&window](){window.close();}),
        Button(sf::Vector2f{50, 50}, sf::Vector2f{0, 0}, static_cast<sf::Texture*>(resourceManger.getResource("resources/brickButton.png"))),
    };

    buttons[0].setText("exit", static_cast<sf::Font*>(resourceManger.getResource("resources/robotto.ttf")), 20.0f, 1.0f);
    buttons[1].setText("brick", static_cast<sf::Font*>(resourceManger.getResource("resources/robotto.ttf")), 20.0f, 0.0f);



    while (window.isOpen()) {

        input.pollEvents();

        for (auto& keyEvnt : input.keyEvents) {
            if (keyEvnt.event.code == sf::Keyboard::Escape)
                window.close();
        }
        for(auto& butt : buttons)
            butt.poll();
        window.clear();
        for(auto& butt: buttons)
            butt.draw(window);
        window.display();
    }

}