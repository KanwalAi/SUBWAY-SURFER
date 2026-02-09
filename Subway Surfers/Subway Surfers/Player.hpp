#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

enum class PlayerState
{
	RUNNING,
	JUMPING,
	SLIDING
};

enum class Lane
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float currentSpeed;
	Lane currentLane;
	PlayerState state;
	float yPosition;
	float jumpVelocity;
	float gravity;
	const float groundY = 450.0f;
	const float lanePositions[3] = { 90.0f, 350.0f, 610.0f };
	bool isTransitioning;
	float targetX;

public:
	Player();
	float getCurrentSpeed() const;
	void setCurrentSpeed(float newSpeed);
	void moveLeft();
	void moveRight();
	void jump();
	void slide();
	void update(float deltaTime);
	void render(sf::RenderWindow& window);
	Lane getCurrentLane() const;
	PlayerState getState() const;
	sf::FloatRect getBounds() const;
	float getYPosition() const;
};

#endif