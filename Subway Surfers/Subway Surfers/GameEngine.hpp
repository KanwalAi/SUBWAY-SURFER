#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Obstacle.hpp"
#include "Train.hpp"
#include "Barrier.hpp"
#include "Cone.hpp"
#include "Fence.hpp"
#include "ScoreManager.hpp"
#include "GameOverScreen.hpp"
using namespace std;
class GameEngine {
private:

	sf::RenderWindow window;
	Player player;

	void updateGameSpeed();
	float speedIncreaseRate;

	void checkCollisions();
	float spawnTimer; // The timer variable
	float continuousSecondTimer;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	float backgroundY;

	sf::Font font;
	ScoreManager scoreManager; // The instance we will use
	GameOverScreen gameOverScreen;
	bool isRunning;
	sf::Clock clock;

	// Obstacles (Changed from unique_ptr to raw pointer for simpler C++ version)
	vector<Obstacle*> obstacles;

public:
	GameEngine();
	~GameEngine(); // Required for manual memory cleanup
	void run();

private:
	void processEvents();
	void handleInput(sf::Keyboard::Key key);
	void update(float deltaTime);
	void render();
	void handleGameOver();
	void spawnObstacle();
};

#endif