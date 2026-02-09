#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP
#include <SFML/Graphics.hpp>
#include <string>
// Abstract base class for all obstacles
class Obstacle
{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	float xPosition;
	float yPosition;
	int lane;
	float speed;

public:
	Obstacle(int lane, float yPos);
	// MUST be virtual for proper memory cleanup of derived classes
	virtual ~Obstacle()
	{
		// No member cleanup needed since sprite/texture are stack allocated
	}

	// Pure virtual function for collision behavior
	virtual bool checkCollision(float playerX, float playerY, bool isJumping, bool isSliding) = 0;

	virtual void update(float deltaTime);
	virtual void render(sf::RenderWindow& window);

	bool isOffScreen() const;
	sf::FloatRect getBounds() const;
	int getLane() const;
};

class Coin : public Obstacle
{
private:
	// Only stores data unique to the coin, like the linked list pointer
	// We don't need sf::Texture, sf::Sprite, speed, etc., as they are inherited.

public:
	// The Coin is now constructed using the Obstacle base constructor
	// Lane enum is implicitly 0, 1, 2, so int lane works fine.
	Coin(int lane);

	// Override the mandatory checkCollision method from Obstacle
	// Coins don't kill the player, but we must implement this virtual function.
	// This will return false for hazards, but true when collected.
	bool checkCollision(float playerX, float playerY, bool isJumping, bool isSliding) override;

	// --- LINKED LIST STRUCTURE (Kept for GameEngine management) ---
	Coin* next;
};

#endif