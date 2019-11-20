#pragma once

#include "GameObject.h"

class ParticleObject : public GameObject
{
public:
	Vector m_velocity;
	Vector m_acceleration;
	float m_life;

	ParticleObject();
	ParticleObject(Sprite* sprite, float life);
	~ParticleObject();
	void setVelocity(Vector vel);
	Vector getVelocity();
	void setAcceleration(Vector acce);
	Vector getAcceleration();
	void setLife(float life);
	float getLife();

	void update();
};