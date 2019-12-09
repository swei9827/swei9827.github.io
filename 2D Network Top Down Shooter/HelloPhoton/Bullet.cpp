#include "Bullet.h"

Bullet::Bullet()
{
	setPos(0.0f, 0.0f);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(1.0f, 1.0f);
	setRotation(0.5f);
	setBlendMode(BlendMode::ADDITIVE);
	radius = 5;
	bounce = 0;
	bouncy = true;
}

Bullet::Bullet(Sprite* sprite)
{
	m_sprite = sprite;
	setPos(0.0f, 0.0f);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(1.0f, 1.0f);
	setBlendMode(BlendMode::ADDITIVE);
	radius = 5;
	bounce = 0;
	bouncy = true;
}

Bullet::Bullet(Sprite* sprite, float x, float y, bool b)
{
	m_sprite = sprite;
	setPos(x, y);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(0.5f, 1.0f);
	setBlendMode(BlendMode::ADDITIVE);
	radius = 5;
	bounce = 0;
	bouncy = b;
}

void Bullet::Target(float speed, Vector pos, float rotation)
{
	setVelocity(pos.mVal[0] * speed, pos.mVal[1] * speed);
	setRotation(rotation);
}

bool Bullet::CheckBoundary()
{
	if (getPos().mVal[0] < 0.0f || getPos().mVal[0] > 800.0f  //check x boundary
		|| getPos().mVal[1] < 0.0f || getPos().mVal[1] > 600.0f ) //check y boundary
	{
		if (bouncy)
		{
			if (bounce < 4)
			{
				//bounce less than 3 times, continue bounce
				if (getPos().mVal[0] < 0.0f)
				{
					setVelocity(Vector(getVelocity().mVal[0] * -1.0f, getVelocity().mVal[1], 0.0f));
					setRotation(getRotation()*-1.0f);
				}
				if (getPos().mVal[0] > 800.0f)
				{
					setVelocity(Vector(getVelocity().mVal[0] * -1.0f, getVelocity().mVal[1], 0.0f));
					setRotation(getRotation()*-1.0f);
				}
				if (getPos().mVal[1] < 0.0f)
				{
					setVelocity(Vector(getVelocity().mVal[0], getVelocity().mVal[1] * -1.0f, 0.0f));
					setRotation(getRotation()*-1.0f);
				}
				if (getPos().mVal[1] > 600.0f)
				{
					setVelocity(Vector(getVelocity().mVal[0], getVelocity().mVal[1] * -1.0f, 0.0f));
					setRotation(getRotation()*-1.0f);
				}
				bounce++;
				return false;
			}
			else
			{
				//bounce more than 3 times
				return true;
			}
		}
		else // not bouncy bullet, and outside boundary
		{
			return true;
		}		
	}
	return false; //inside boundary
}

bool Bullet::circleCollision(Obstacle* go)
{
	float collided = radius + go->radius;
	Vector vec = getPos() - go->getPos();
	float distance = sqrtf((vec.mVal[0] * vec.mVal[0]) + (vec.mVal[1] * vec.mVal[1]));
	if (collided > distance)
	{
		setVelocity(getVelocity() * -1.0f);
		return true;
	}
	else
	{
		return false;
	}
}

Bullet::~Bullet()
{
}
