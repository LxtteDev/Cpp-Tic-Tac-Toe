#include <iostream>
#include <SFML/Graphics.hpp>

int main(int, char**) {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic Tac Toe");

     while (window.isOpen()) {
        // sf::Time deltaTime = clock.restart();
        // float deltaSeconds = deltaTime.asSeconds();

        sf::Event e;
		while (window.pollEvent(e))
			if (e.type == sf::Event::Closed)
                window.close();

        std::cout << "Drawing scene" << std::endl;
        window.display();
    }

    window.close();
}
