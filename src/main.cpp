#include <iostream>
#include <SFML/Graphics.hpp>

const int unsigned barSize = 4;

void drawLines(sf::RenderWindow& window, sf::Vector2u size) {
    int yHalf = size.y / 2;
    int xHalf = size.x / 2;

    // Not very complex math
    int bar = (size.x >= size.y ? size.y : size.x) - 2 * barSize;

    int y = yHalf - bar / 2;
    int x1 = xHalf - bar / 6 - 2; 
    int x2 = xHalf + bar / 6 - 2; 

    int x = xHalf - bar / 2;
    int y1 = yHalf - bar / 6 - 2; 
    int y2 = yHalf + bar / 6 - 2; 

    // Vertical Bars
    sf::RectangleShape vert1;
    sf::RectangleShape vert2;

    vert1.setSize(sf::Vector2f(barSize, bar));
    vert2.setSize(sf::Vector2f(barSize, bar));

    vert1.setPosition(sf::Vector2f(x1, y));
    vert2.setPosition(sf::Vector2f(x2, y));

    window.draw(vert1);
    window.draw(vert2);

    // Horizontal bars
    sf::RectangleShape horz1;
    sf::RectangleShape horz2;

    horz1.setSize(sf::Vector2f(bar, barSize));
    horz2.setSize(sf::Vector2f(bar, barSize));

    horz1.setPosition(sf::Vector2f(x, y1));
    horz2.setPosition(sf::Vector2f(x, y2));

    window.draw(horz1);
    window.draw(horz2);
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
