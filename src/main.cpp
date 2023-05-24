#include <iostream>
#include <SFML/Graphics.hpp>

const int unsigned barSize = 4;

void drawLines(sf::RenderWindow& window, sf::Vector2u size) {
    if (size.x >= size.y) {
        int yHalf = size.y / 2;
        int xHalf = size.x / 2;

        // Not very complex math
        int height = size.y - 2 * barSize;

        int y = yHalf - height / 2;
        int x1 = xHalf - height / 6 - 2; 
        int x2 = xHalf + height / 6 - 2; 

        // Vertical Bars
        sf::RectangleShape vert1;
        sf::RectangleShape vert2;

        vert1.setSize(sf::Vector2f(barSize, height));
        vert2.setSize(sf::Vector2f(barSize, height));
    
        vert1.setPosition(sf::Vector2f(x1, y));
        vert2.setPosition(sf::Vector2f(x2, y));
    
        window.draw(vert1);
        window.draw(vert2);
    }
}

int main(int, char**) {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic Tac Toe");

     while (window.isOpen()) {
        // sf::Time deltaTime = clock.restart();
        // float deltaSeconds = deltaTime.asSeconds();

        sf::Event e;
		while (window.pollEvent(e))
			if (e.type == sf::Event::Closed)
                window.close();
            else if (e.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));

        window.clear();

        // Render lines
        drawLines(window, window.getSize());

        window.display();
    }

    window.close();
}
