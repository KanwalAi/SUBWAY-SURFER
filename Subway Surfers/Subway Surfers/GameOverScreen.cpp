#include "GameOverScreen.hpp"
#include <sstream>

GameOverScreen::GameOverScreen(sf::Font& gameFont)
    : font(gameFont)
{
    // --- Title Text Setup (GAME OVER) ---
    titleText.setFont(font);
    titleText.setString("G A M E   O V E R");
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::Red);
    // Setting origin to center for easy positioning
    titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);

    // --- Score Text Setup ---
    scoreText.setFont(font);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color::White);

    // --- Instruction Text Setup ---
    instructionText.setFont(font);
    instructionText.setString("Press ESC to Exit");
    instructionText.setCharacterSize(20);
    instructionText.setFillColor(sf::Color(180, 180, 180));
}

void GameOverScreen::render(sf::RenderWindow& window, int finalScore)
{
    sf::Vector2u windowSize = window.getSize();
    float centerX = windowSize.x / 2.0f;
    float centerY = windowSize.y / 2.0f;

    // Draw Background Overlay (Semi-transparent black)
    sf::RectangleShape overlay(sf::Vector2f((float)windowSize.x, (float)windowSize.y));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);

    // Position and Draw Title
    titleText.setOrigin(titleText.getLocalBounds().width / 2, titleText.getLocalBounds().height / 2);
    titleText.setPosition(centerX, centerY - 100);
    window.draw(titleText);

    // Update Score Text
    std::stringstream ss;
    ss << "F I N A L   S C O R E : " << finalScore;
    scoreText.setString(ss.str());

    // Position and Draw Score
    scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
    scoreText.setPosition(centerX, centerY + 20);
    window.draw(scoreText);

    // Position and Draw Instruction
    instructionText.setOrigin(instructionText.getLocalBounds().width / 2, instructionText.getLocalBounds().height / 2);
    instructionText.setPosition(centerX, centerY + 100);
    window.draw(instructionText);

}