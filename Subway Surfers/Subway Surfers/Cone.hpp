#ifndef CONE_HPP
#define CONE_HPP

#include "Obstacle.hpp"

class Cone : public Obstacle
{
public:
	Cone(int lane, float yPos);
	bool checkCollision(float playerX, float playerY, bool isJumping, bool isSliding) override;
};

#endif