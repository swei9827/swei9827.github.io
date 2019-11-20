#include "ParticleObject.h"

ParticleObject::ParticleObject()
{

}

ParticleObject::ParticleObject(Sprite* sprite, float life)
{
	setSprite(sprite);
	m_life = life;
	m_velocity = Vector(0.0f, 0.0f, 0.0f);
}

ParticleObject::~ParticleObject()
{
	std::cout << "Destruct Particle Object" << std::endl;
	delete this;
}

void ParticleObject::setVelocity(Vector vel)
{
	m_velocity = vel;
}

Vector ParticleObject::getVelocity()
{
	return m_velocity;
}

void ParticleObject::setAcceleration(Vector acce)
{
	m_acceleration = acce;
}

Vector ParticleObject::getAcceleration()
{
	return m_acceleration;
}

void ParticleObject::setLife(float life)
{
	m_life = life;
}

float ParticleObject::getLife()
{
	return m_life;
}

void ParticleObject::update()
{
	//============update the position

	//acceleration affects velocity,
	//velocity affects position
	
	if (m_life > 0)
	{
		m_velocity += m_acceleration;
		setPos(getPos() + m_velocity);
	}
	else
	{
		delete this;
	}

	//decrease the life of particle every update;
	m_life--;
}