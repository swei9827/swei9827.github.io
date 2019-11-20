#pragma once
#include <list>
#include "ParticleObject.h"
#include "ParticleAffector.h"

enum EmitterShape
{
	CIRCLE = 0,
	SQUARE,
	POINTSHAPE,
	TOTAL
};

class ParticleSystem
{
private:
	std::list<ParticleObject*> m_particleList;
	std::list<ParticleAffector*> m_affectorList;
	Sprite* m_pSprite;
	float emissionRate;
	int emissionCount;
	Vector m_position;
	float currentTime;
	EmitterShape m_emitterShape;

public:
	ParticleSystem(Sprite* sprite);
	void setPos(Vector pos);
	Vector getPos();
	void setEmissionRate(float e);
	void update(float time);
	void addParticle();
	void draw(void);
	void setShape(ParticleObject* po);
};

//ParticleSystem
//+list of particle object
//+list of particle affectors
//+emitterShape(set to null by default, null:point emiiter)
