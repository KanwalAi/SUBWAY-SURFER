#include "Player.hpp"
#include <iostream>
using namespace std;
Player::Player() : currentLane(Lane::MIDDLE), state(PlayerState::RUNNING), yPosition(500.0f), jumpVelocity(0.0f), gravity(980.0f), isTransitioning(false), targetX(lanePositions[1]), currentSpeed(300.0f)
{

	// Load player texture
	if (!texture.loadFromFile("player.png"))
	{
		cout << "Error loading player texture!" << endl;
		// Create a placeholder rectangle if texture fails
		texture.create(50, 80);
	}

	sprite.setTexture(texture);
	sprite.setPosition(lanePositions[1], yPosition);
	sprite.setScale(0.5f, 0.5f);
}

// ---------------- Getter ----------------
//  NEW: Function to let GameEngine read the current speed
float Player::getCurrentSpeed() const
{
	return currentSpeed;
}

// ---------------- Setter ----------------
//  NEW: Function to let GameEngine increase the speed periodically
void Player::setCurrentSpeed(float newSpeed)
{
	// Ensure speed doesn't decrease and stays above a minimum
	if (newSpeed > 300.0f) {
		currentSpeed = newSpeed;
	}
}
void Player::moveLeft()
{
	if (state == PlayerState::SLIDING) return;

	if (currentLane == Lane::MIDDLE)
	{
		currentLane = Lane::LEFT;
		targetX = lanePositions[0];
		isTransitioning = true;
	}
	else if (currentLane == Lane::RIGHT)
	{
		currentLane = Lane::MIDDLE;
		targetX = lanePositions[1];
		isTransitioning = true;
	}
}
void Player::moveRight()
{
	if (state == PlayerState::SLIDING) return;
	if (currentLane == Lane::LEFT)
	{
		currentLane = Lane::MIDDLE;
		targetX = lanePositions[1];
		isTransitioning = true;
	}
	else if (currentLane == Lane::MIDDLE)
	{
		currentLane = Lane::RIGHT;
		targetX = lanePositions[2];
		isTransitioning = true;
	}
}

void Player::jump()
{
	if (state == PlayerState::RUNNING)
	{
		state = PlayerState::JUMPING;
		jumpVelocity = -600.0f;
	}
}

void Player::slide()
{
	if (state == PlayerState::RUNNING)
	{
		state = PlayerState::SLIDING;
	}
}

void Player::update(float deltaTime)
{
	// Handle lane transition
	if (isTransitioning)
	{
		float currentX = sprite.getPosition().x;
		float diff = targetX - currentX;

		if (abs(diff) < 5.0f)
		{
			sprite.setPosition(targetX, sprite.getPosition().y);
			isTransitioning = false;
		}
		else {
			sprite.move(diff * 10.0f * deltaTime, 0);
		}
	}

	// Handle jumping
	if (state == PlayerState::JUMPING)
	{
		jumpVelocity += gravity * deltaTime;
		yPosition += jumpVelocity * deltaTime;

		if (yPosition >= groundY)
		{
			yPosition = groundY;
			jumpVelocity = 0.0f;
			state = PlayerState::RUNNING;
		}
	}

	// Handle sliding - return to running after brief period
	if (state == PlayerState::SLIDING)
	{
		static float slideTimer = 0.0f;
		slideTimer += deltaTime;
		if (slideTimer >= 0.5f)
		{
			state = PlayerState::RUNNING;
			slideTimer = 0.0f;
		}
	}

	sprite.setPosition(sprite.getPosition().x, yPosition);
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

Lane Player::getCurrentLane() const
{
	return currentLane;
}

PlayerState Player::getState() const
{
	return state;
}

sf::FloatRect Player::getBounds() const
{
	return sprite.getGlobalBounds();
}

float Player::getYPosition() const
{
	return yPosition;
}