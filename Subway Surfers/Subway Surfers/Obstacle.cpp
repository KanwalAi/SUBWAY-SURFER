#include "Obstacle.hpp"
#include <iostream>

const float LANE_X_POSITIONS[] = { 150.0f, 400.0f, 650.0f };
const std::string COIN_TEXTURE_PATH = "coin.png";
// ---------------- Constructor ----------------
Obstacle::Obstacle(int lane, float yPos)
{
	this->lane = lane;
	this->yPosition = yPos;

	// Set correct X-position based on lane
	// Adjust these values to match your track width
	if (lane == 0) {
		xPosition = 90;
	}
	else if (lane == 1) {
		xPosition = 350;
	}
	else {
		xPosition = 610;
	}
	speed = 300.0f; // obstacle falling speed

	// Initial sprite position
	sprite.setPosition(xPosition, yPosition);
}

// ---------------- Update Movement ----------------
void Obstacle::update(float deltaTime)
{
	yPosition += speed * deltaTime;
	sprite.setPosition(xPosition, yPosition);
}

// ---------------- Render ----------------
void Obstacle::render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

// ---------------- Screen Check ----------------
bool Obstacle::isOffScreen() const
{
	return yPosition > 650; // below window
}

// ---------------- Collision Bounds ----------------
sf::FloatRect Obstacle::getBounds() const
{
	return sprite.getGlobalBounds();
}

// ---------------- Lane Getter ----------------
int Obstacle::getLane() const
{
	return lane;
}

// ---------------- Coin Constructor ----------------
Coin::Coin(int lane)
// Initialize the base Obstacle class
	: Obstacle(lane, -100.0f)
{
	speed = 300.0;
	// Override position to match the Coin's specific lane centers
	xPosition = LANE_X_POSITIONS[lane];
	yPosition = -100.0f; // Coins start high

	// The Coin needs to load its own specific texture
	if (!texture.loadFromFile(COIN_TEXTURE_PATH)) {
		std::cerr << "Error loading coin texture: " << COIN_TEXTURE_PATH << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);

	// Set final sprite position
	sprite.setPosition(xPosition, yPosition);

	// Also set speed from the GameEngine (player's current speed)
}

// ---------------- Coin Collision (Satisfies virtual function) ----------------
bool Coin::checkCollision(float playerX, float playerY, bool isJumping, bool isSliding)
{
	// A coin is not a traditional obstacle (it doesn't kill the player).
	// We will rely on GameEngine::checkCollisions() to use getBounds() and 
	// dynamic_cast to identify a coin and handle scoring/deletion.

	// For safety, we return false here so this function doesn't accidentally
	// trigger a Game Over when used in the primary obstacle collision loop.
	return false;
}