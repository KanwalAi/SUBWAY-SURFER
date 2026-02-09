#ifndef TRAIN_HPP
#define TRAIN_HPP

#include "Obstacle.hpp"

class Train : public Obstacle
{
public:
	Train(int lane, float yPos);
	virtual ~Train() = default;

	bool checkCollision(float playerX, float playerY,
		bool isJumping, bool isSliding) override;
};

#endif