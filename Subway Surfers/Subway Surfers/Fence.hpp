#ifndef FENCE_HPP
#define FENCE_HPP

#include "Obstacle.hpp"

class Fence : public Obstacle
{
public:
	Fence(int lane, float yPos);
	bool checkCollision(float playerX, float playerY, bool isJumping, bool isSliding) override;
};

#endif