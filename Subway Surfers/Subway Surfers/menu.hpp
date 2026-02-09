#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class MenuResult {
    None,
    StartGame,
    Instructions,
    ExitGame
};

class Menu {
public:
    Menu(const sf::Font& font, unsigned int windowW, unsigned int windowH);

    MenuResult handleEvent(const sf::Event& event);
    void update(float dt);
    void render(sf::RenderWindow& window);

    void loadBackground(const std::string& path);

private:
    const sf::Font& font;
    unsigned int w, h;

    sf::Text title;
    std::vector<sf::Text> items;
    size_t selectedIndex = 0;

    // Colors & sizes
    sf::Color normalColor = sf::Color::White;
    sf::Color selectedColor = sf::Color::Black;
    unsigned int titleSize = 62;
    unsigned int itemSize = 30;

    // background support
    sf::Texture bgTexture;
    sf::Sprite  bgSprite;
    bool bgLoaded = false;

    void updateTextPositions();
};
