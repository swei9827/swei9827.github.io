#include "Obstacle.h"

Obstacle::Obstacle()
{
	setPos(0.0f, 0.0f);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(1.0f, 1.0f);
	setRotation(0.5f);
	setBlendMode(BlendMode::ADDITIVE);
	isSquare = true;
	radius = 80;
}

Obstacle::Obstacle(Sprite* sprite, bool s, float r)
{
	m_sprite = sprite;
	setPos(0.0f, 0.0f);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(1.0f, 1.0f);
	setBlendMode(BlendMode::ADDITIVE);
	isSquare = s;
	radius = r;
}

Obstacle::Obstacle(Sprite* sprite, float x, float y, bool s, float r)
{
	m_sprite = sprite;
	setPos(x, y);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(0.5f, 1.0f);
	setBlendMode(BlendMode::ADDITIVE);
	isSquare = s;
	radius = r;
}

Obstacle::~Obstacle()
{
}
