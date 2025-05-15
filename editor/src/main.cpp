#include <SFML/Graphics.hpp>

#include "InputState.hpp"
#include "ResourceManager.hpp"
#include "Button.hpp"


int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Peg Edit", sf::Style::Default);
    window.setFramerateLimit(60);

    InputState::initalise(&window);
    InputState& input = InputState::getRef();

    Button button({ 100, 100 }, { 0,0 }, "resources/extIco.png", [&window]() {window.close(); });

    while (window.isOpen()) {

        input.pollEvents();

        for (auto& keyEvnt : input.keyEvents) {
            if (keyEvnt.event.code == sf::Keyboard::Escape)
                window.close();
        }

        button.poll();

        window.clear();
        window.draw(button.getShape());
        window.draw(button.getTintShape());
        window.display();

    }

    ResourceManager::getRef().unload();

}