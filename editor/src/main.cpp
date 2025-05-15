#include <SFML/Graphics.hpp>

#include "InputState.hpp"

int main(){
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Peg Edit", sf::Style::Default);
    window.setFramerateLimit(60);

    InputState::initalise(&window);
    InputState& input = InputState::getRef();
    
    while(window.isOpen()){

        input.pollEvents();

        for(auto& keyEvnt : input.keyEvents){
            if(keyEvnt.event.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear();
        window.display();

    }

}