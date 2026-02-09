#include "ScoreManager.hpp"
#include <fstream>
#include <iostream>

using namespace std;

ScoreManager::ScoreManager(sf::Font& gameFont)
    : currentScore(0), font(gameFont)
{
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(650, 10);

    for (int i = 0; i < MAX_ENTRIES; ++i)
        topScores[i] = 0;
}

// In-game score
void ScoreManager::addScore(int points)
{
    currentScore += points;
    cout << "Score updated: " << currentScore << endl;
}

void ScoreManager::update(float deltaTime)
{
    scoreText.setString("Score: " + std::to_string(currentScore));
}

void ScoreManager::render(sf::RenderWindow& window)
{
    window.draw(scoreText);
}

int ScoreManager::getScore() const
{
    return static_cast<int>(currentScore);
}

long long ScoreManager::getCurrentScore() const
{
    return currentScore;
}

// File-based scores
void ScoreManager::loadScoresFromFile(const char* filename)
{
    std::ifstream file(filename);
    for (int i = 0; i < MAX_ENTRIES; ++i)
        topScores[i] = 0;

    if (!file.is_open()) return;

    for (int i = 0; i < MAX_ENTRIES && file >> topScores[i]; ++i)
        ;
    file.close();
}

void ScoreManager::saveScoresToFile(const char* filename)
{
    std::ofstream file(filename);
    for (int i = 0; i < MAX_ENTRIES; ++i)
        file << topScores[i] << "\n";
    file.close();
}

bool ScoreManager::insertNewScore(int score)
{
    for (int i = 0; i < MAX_ENTRIES; ++i)
    {
        if (score > topScores[i])
        {
            for (int j = MAX_ENTRIES - 1; j > i; --j)
                topScores[j] = topScores[j - 1];
            topScores[i] = score;
            return true;
        }
    }
    return false;
}
