// COIN.HPP

#ifndef COIN_HPP
#define COIN_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Coin {
public:
    enum Lane { LEFT, MIDDLE, RIGHT };

private:
    sf::Texture texture;
    sf::Sprite sprite;
    Lane currentLane;
    float speed;
    float positionY;

public:
    Coin(Lane lane, float initialSpeed);
    ~Coin() = default;

    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isOffScreen() const;

    // --- LINKED LIST STRUCTURE ---
    // Public pointer to the next coin in the list.
    // This allows GameEngine to traverse the list without exposing all Coin internals.
    Coin* next;
};

#endif