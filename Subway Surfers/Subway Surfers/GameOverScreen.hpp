#ifndef GAMEOVERSCREEN_HPP
#define GAMEOVERSCREEN_HPP

#include <SFML/Graphics.hpp>

class GameOverScreen {
private:
    // Reference to the font loaded in GameEngine
    sf::Font& font;
    sf::Text titleText;
    sf::Text scoreText;
    sf::Text instructionText;

public:
    // Constructor takes a reference to the font
    GameOverScreen(sf::Font& gameFont);

    // Draws the Game Over screen with the provided final score
    void render(sf::RenderWindow& window, int finalScore);
};

#endif