#pragma once
#include "GameObject.h"

class Obstacle : public GameObject
{
public:
	bool isSquare;

	Obstacle();
	Obstacle(Sprite* sprite, bool s, float r);
	Obstacle(Sprite* sprite, float x, float y, bool s, float r);

	~Obstacle();
};
