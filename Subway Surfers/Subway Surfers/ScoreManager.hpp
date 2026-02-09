#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <string>

const int MAX_ENTRIES = 10;

class ScoreManager
{
private:
    long long currentScore;
    sf::Font& font;
    sf::Text scoreText;

    int topScores[MAX_ENTRIES];

public:
    ScoreManager(sf::Font& gameFont);

    // In-game score
    void addScore(int points);
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    long long getCurrentScore() const;

    // File-based top scores
    void loadScoresFromFile(const char* filename);
    void saveScoresToFile(const char* filename);
    bool insertNewScore(int score);

    int getScore() const;
};

#endif
