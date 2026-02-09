#include "Menu.hpp"
#include <iostream>

Menu::Menu(const sf::Font& f, unsigned int windowW, unsigned int windowH)
    : font(f), w(windowW), h(windowH)
{
    title.setFont(font);
    title.setCharacterSize(38);         
    title.setFillColor(sf::Color::Black);
    title.setStyle(sf::Text::Bold);


    title.setString("SUBWAY SURFERS 2D");

    std::vector<std::string> options = { "Start Game", "Instructions", "Exit" };
    items.clear();

    for (auto& txt : options) {
        sf::Text t;
        t.setFont(font);
        t.setCharacterSize(itemSize);
        t.setString(txt);
        t.setFillColor(sf::Color::Black);
        t.setStyle(sf::Text::Bold);
        items.push_back(t);
    }
    for (auto& t : items) {
        t.setOutlineColor(sf::Color(255, 255, 255)); // white outline
        t.setOutlineThickness(2.f);
    }

    updateTextPositions();
}

void Menu::loadBackground(const std::string& path)
{
    if (bgTexture.loadFromFile(path)) {
        bgLoaded = true;
        bgSprite.setTexture(bgTexture);

        sf::Vector2u texSize = bgTexture.getSize();
        float sx = static_cast<float>(w) / texSize.x;
        float sy = static_cast<float>(h) / texSize.y;
        bgSprite.setScale(sx, sy);
    }
    else {
        std::cout << "Menu background not found: " << path << "\n";
        bgLoaded = false;
    }
}

void Menu::updateTextPositions()
{
    sf::FloatRect b = title.getLocalBounds();
    title.setOrigin(b.width / 2, b.height / 2);
    title.setPosition(w / 2, h * 0.10f);

    float startY = h * 0.32f;
    float gap = 48.f;

    for (size_t i = 0; i < items.size(); ++i) {
        sf::FloatRect ib = items[i].getLocalBounds();
        items[i].setOrigin(ib.width / 2, ib.height / 2);
        items[i].setPosition(w / 2, startY +2* i * gap);

        items[i].setFillColor(sf::Color::Black);

        if (i == selectedIndex) {
            items[i].setOutlineColor(sf::Color(120, 120, 120));
            items[i].setOutlineThickness(3.f);
        }
        else {
            items[i].setOutlineThickness(0.f);
        }
    }
}


MenuResult Menu::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
            selectedIndex = (selectedIndex == 0 ? items.size() - 1 : selectedIndex - 1);
            updateTextPositions();
        }
        else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
            selectedIndex = (selectedIndex + 1) % items.size();
            updateTextPositions();
        }
        else if (event.key.code == sf::Keyboard::Return) {
            switch (selectedIndex) {
            case 0: return MenuResult::StartGame;
            case 1: return MenuResult::Instructions;
            case 2: return MenuResult::ExitGame;
            }
        }
    }
    return MenuResult::None;
}

void Menu::update(float dt)
{
    // add animations later if you like
}

void Menu::render(sf::RenderWindow& window)
{
    if (bgLoaded) {
        window.draw(bgSprite);
    }
    else {
        sf::RectangleShape bg(sf::Vector2f((float)w, (float)h));
        bg.setFillColor(sf::Color(25, 35, 55));
        window.draw(bg);
    }

    window.draw(title);

    for (auto& t : items)
        window.draw(t);

    // footer
    sf::Text hint;
    hint.setFont(font);
    hint.setCharacterSize(16);
    hint.setFillColor(sf::Color::White);
    hint.setString("Use Arrow Keys or W/S and Press Enter");
    sf::FloatRect hb = hint.getLocalBounds();
    hint.setOrigin(hb.width / 2, hb.height / 2);
    hint.setPosition(w / 2, h * 0.9f);
    window.draw(hint);
}
