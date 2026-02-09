#pragma once
#ifndef BARRIER_HPP
#define BARRIER_HPP

#include "Obstacle.hpp"

class Barrier : public Obstacle
{
public:
	Barrier(int lane, float yPos);
	bool checkCollision(float playerX, float playerY, bool isJumping, bool isSliding) override;
};

#endif