#include <iostream>
#include <SFML/Graphics.hpp>

const int unsigned barSize = 4;
int board[3][3] = { // -1 -> Empty; 0 -> X; 1 -> O
    { -1, -1, -1 },
    { -1, -1, -1 },
    { -1, -1, -1 }
};
bool turn = 0; // 0 -> X; 1 -> O

sf::Texture xImage;
sf::Texture oImage;

void drawLines(sf::RenderWindow& window, sf::Vector2u size) {
    int yHalf = size.y / 2;
    int xHalf = size.x / 2;

    // Not very complex math
    int bar = std::min(size.x, size.y) - barSize * 2;

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

void click(sf::Vector2u size, sf::Vector2i position) {
    int boardSize = std::min(size.x, size.y) - barSize * 2;
    int boardSizeThree = (boardSize - boardSize % 3) / 3;
    sf::Vector2i boardPosition = size.x >= size.y ? sf::Vector2i((size.x - boardSize) / 2, barSize) : sf::Vector2i(barSize, (size.y - boardSize) / 2);

    if (position.x > boardPosition.x && position.x < boardPosition.x + boardSize && position.y > boardPosition.y && position.y < boardPosition.y + boardSize) {
        sf::Vector2i mousePosition = position - boardPosition; // Position of mouse on board

        int x = mousePosition.x > boardSizeThree * 2 ? 2 : mousePosition.x > boardSizeThree ? 1 : 0;
        int y = mousePosition.y > boardSizeThree * 2 ? 2 : mousePosition.y > boardSizeThree ? 1 : 0;
        
        if (board[x][y] == -1) {
            board[x][y] = turn;
            turn = !turn;
        }
    }
}

void displayBoard(sf::RenderWindow& window, sf::Vector2u size) {
    int boardSize = std::min(size.x, size.y) - barSize * 2;
    int tileSize = (boardSize - boardSize % 3) / 3 - barSize * 2;
    sf::Vector2i boardPosition = size.x >= size.y ? sf::Vector2i((size.x - boardSize) / 2, barSize) : sf::Vector2i(barSize, (size.y - boardSize) / 2);

    for (unsigned int y = 0; y < 3; y++) {
        for (unsigned int x = 0; x < 3; x++) {
            int tileState = board[x][y];

            if (tileState == -1) continue;

            sf::Sprite tile;
            tile.setPosition(x * tileSize + (x + 1) * barSize + boardPosition.x, y * tileSize + (y + 1) * barSize + boardPosition.y);
            tile.setScale((float)tileSize / 64.0f, (float)tileSize / 64.0f);
            tile.setTexture(tileState == 0 ? xImage : oImage);

            window.draw(tile);
        }
    }
}

int main(int, char**) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tic Tac Toe");

    xImage.loadFromFile("img/X.png");
    oImage.loadFromFile("img/O.png");

    bool mouseLock = false;

    while (window.isOpen()) {
        // sf::Time deltaTime = clock.restart();
        // float deltaSeconds = deltaTime.asSeconds();

        sf::Event e;
		while (window.pollEvent(e))
			if (e.type == sf::Event::Closed)
                window.close();
            else if (e.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect(0, 0, e.size.width, e.size.height)));
            else if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left && !mouseLock) {
                click(window.getSize(), sf::Mouse::getPosition() - window.getPosition() - sf::Vector2i(0, 30));
                mouseLock = true;
            } else if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left && mouseLock)
                mouseLock = false;

        window.clear();

        drawLines(window, window.getSize());
        displayBoard(window, window.getSize());

        window.display();
    }

    window.close();
}
