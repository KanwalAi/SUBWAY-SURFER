#include "GameEngine.hpp"
#include "Menu.hpp"
#include <iostream>
#include <cstdlib> // rand
using namespace std;
const char* SCORE_FILE = "scores.txt"; 
GameEngine::GameEngine()
    : window(sf::VideoMode(800, 600), "Subway Surfers - OOP Project"),
    backgroundY(0.0f),
    speedIncreaseRate(20.0f),
    isRunning(true),
    spawnTimer(0.0f),
    continuousSecondTimer(0.0f),
    scoreManager(font),
    gameOverScreen(font)
{
    window.setFramerateLimit(60);

    if (!font.loadFromFile("arial.ttf"))
        cout << "Error loading font!" << endl;

    if (!backgroundTexture.loadFromFile("background.png")) {
        cout << "Error loading background!" << endl;
        sf::Image img; img.create(800, 600, sf::Color(50, 50, 100));
        backgroundTexture.loadFromImage(img);
    }
    backgroundSprite.setTexture(backgroundTexture);
    sf::Vector2u texSize = backgroundTexture.getSize();
    backgroundSprite.setScale(800.0f / texSize.x, 600.0f / texSize.y);
}

GameEngine::~GameEngine()
{
    for (auto o : obstacles) delete o;
    obstacles.clear();
}

void GameEngine::run()
{
    Menu menu(font, 800, 600);
    menu.loadBackground("menu_background.jpg");
    bool inMenu = true;

    while (inMenu && window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); return; }

            MenuResult r = menu.handleEvent(event);
            if (r == MenuResult::StartGame) inMenu = false;
            else if (r == MenuResult::Instructions)
            {
                sf::Text info;
                info.setFont(font); info.setCharacterSize(22); info.setFillColor(sf::Color::White);
                info.setString("A/D or Left/Right: Move\nW: Jump\nS: Slide\n\nPress ENTER to return...");
                info.setPosition(150, 180);

                bool waiting = true;
                while (waiting && window.isOpen())
                {
                    sf::Event e2;
                    while (window.pollEvent(e2))
                    {
                        if (e2.type == sf::Event::Closed) { window.close(); return; }
                        if (e2.type == sf::Event::KeyPressed && e2.key.code == sf::Keyboard::Return)
                            waiting = false;
                    }
                    window.clear(sf::Color::Black);
                    window.draw(info);
                    window.display();
                }
            }
            else if (r == MenuResult::ExitGame)
            {
                window.close(); return;
            }
        }

        window.clear();
        menu.render(window);
        window.display();
    }

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        processEvents();
        if (isRunning) update(dt);
        render();
    }
}

void GameEngine::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) { window.close(); return; }
        if (event.type == sf::Event::KeyPressed)
        {
            if (isRunning) handleInput(event.key.code);
            else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Escape)
                window.close();
        }
    }
}

void GameEngine::handleInput(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::A: case sf::Keyboard::Left: player.moveLeft(); break;
    case sf::Keyboard::D: case sf::Keyboard::Right: player.moveRight(); break;
    case sf::Keyboard::W: case sf::Keyboard::Up: case sf::Keyboard::Space: player.jump(); break;
    case sf::Keyboard::S: case sf::Keyboard::Down: player.slide(); break;
    case sf::Keyboard::Escape: isRunning = false; break;
    }
}

void GameEngine::update(float deltaTime)
{
    if (!isRunning) return;

    float currentSpeed = player.getCurrentSpeed();
    float baseInterval = 1.5f;
    float speedScalingFactor = 0.002f;
    float targetInterval = baseInterval - (currentSpeed * speedScalingFactor);
    if (targetInterval < 0.5f) targetInterval = 0.5f;

    player.update(deltaTime);
    spawnTimer += deltaTime;
    if (spawnTimer >= targetInterval) { spawnObstacle(); spawnTimer = 0.0f; }

    for (auto o : obstacles) o->update(deltaTime);

    checkCollisions();

    scoreManager.update(deltaTime);
    continuousSecondTimer += deltaTime;
    if (continuousSecondTimer >= 1.0f)
    {
        scoreManager.addScore(10);
        updateGameSpeed();
        continuousSecondTimer -= 1.0f;
    }

    for (int i = obstacles.size() - 1; i >= 0; --i)
    {
        if (obstacles[i]->isOffScreen()) { delete obstacles[i]; obstacles.erase(obstacles.begin() + i); }
    }
}

void GameEngine::updateGameSpeed()
{
    player.setCurrentSpeed(player.getCurrentSpeed() + speedIncreaseRate);
}

void GameEngine::spawnObstacle()
{
    int lane = rand() % 3;
    int type = rand() % 5;
    float yPos = -100.0f;

    Obstacle* newObstacle = nullptr;

    if (type == 4) newObstacle = new Coin(lane);
    else
    {
        switch (type)
        {
        case 0: newObstacle = new Train(lane, yPos); break;
        case 1: newObstacle = new Barrier(lane, yPos); break;
        case 2: newObstacle = new Cone(lane, yPos); break;
        case 3: newObstacle = new Fence(lane, yPos); break;
        }
    }

    if (newObstacle) obstacles.push_back(newObstacle);
}

void GameEngine::checkCollisions()
{
    sf::FloatRect playerBounds = player.getBounds();
    bool isJumping = (player.getState() == PlayerState::JUMPING);
    bool isSliding = (player.getState() == PlayerState::SLIDING);

    vector<int> indicesToDelete;

    for (size_t i = 0; i < obstacles.size(); ++i)
    {
        Obstacle* current = obstacles[i];

        if (playerBounds.intersects(current->getBounds()))
        {
            if (Coin* coin = dynamic_cast<Coin*>(current))
            {
                scoreManager.addScore(50);
                indicesToDelete.push_back(i);
                continue;
            }
            else
            {
                if (current->checkCollision(playerBounds.left, playerBounds.top, isJumping, isSliding))
                {
                    isRunning = false;
                    cout << "!!! GAME OVER !!! Collision detected..." << endl;

                    // Save score to file
                    // Save top score on game over
                    scoreManager.loadScoresFromFile(SCORE_FILE);
                    if (scoreManager.insertNewScore(scoreManager.getScore()))
                        scoreManager.saveScoresToFile(SCORE_FILE);


                    return;
                }
            }
        }
    }

    for (int i = indicesToDelete.size() - 1; i >= 0; --i)
    {
        int index = indicesToDelete[i];
        delete obstacles[index];
        obstacles.erase(obstacles.begin() + index);
    }
}


void GameEngine::render()
{
    window.clear();

    if (isRunning)
    {
        backgroundSprite.setPosition(0, 0);
        window.draw(backgroundSprite);

        // Lane markers
        sf::RectangleShape leftLane(sf::Vector2f(2, 600));
        leftLane.setPosition(265, 0); leftLane.setFillColor(sf::Color::White); window.draw(leftLane);
        sf::RectangleShape rightLane(sf::Vector2f(2, 600));
        rightLane.setPosition(535, 0); rightLane.setFillColor(sf::Color::White); window.draw(rightLane);

        player.render(window);
        for (auto o : obstacles) o->render(window);
        scoreManager.render(window);

        sf::Text instructions;
        instructions.setFont(font); instructions.setString("A/D: Move  W: Jump  S: Slide  ESC: End Game");
        instructions.setCharacterSize(16); instructions.setFillColor(sf::Color::White);
        instructions.setPosition(10, 10); window.draw(instructions);
    }
    else
    {
        gameOverScreen.render(window, scoreManager.getScore());
    }

    window.display();
}
