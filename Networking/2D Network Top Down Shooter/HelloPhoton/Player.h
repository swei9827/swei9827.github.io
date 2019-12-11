#pragma once

#include "GameObject.h"
#include "Bullet.h"
#include "Obstacle.h"

class Player : public GameObject
{
private:
	int m_health;
	Sprite* m_hpSprite;

public:
	Player();
	Player(Sprite* sprite);
	Player(Sprite* sprite, float x, float y);

	void setUISprite(Sprite* hpSprite);
	void ShowHealth();
	void setHealth(int hp);
	int getHealth();

	void borderCheck();
	int rectCollision(Player* go1, Bullet* go2);

	bool circleCollision(Bullet* go);
	bool circleCollision(Player* go);
	bool circleCollision(Obstacle* go);

	void update(double elapsedTime) override;
	void draw() override;
	
	~Player();
};
