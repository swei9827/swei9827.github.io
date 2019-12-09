#pragma once
#include "GameObject.h"
#include "Obstacle.h"

class Bullet : public GameObject
{
private:
	int damage;	
	bool bouncy;

public:
	int bounce;

	Bullet();
	Bullet(Sprite* sprite);
	Bullet(Sprite* sprite, float x, float y, bool b);

	void Target(float speed, Vector pos, float rotation);
	bool CheckBoundary();
	bool circleCollision(Obstacle* go);

	~Bullet();
};
