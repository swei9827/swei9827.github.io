#pragma once
#include "Sprite.h"
#include "vector.h"
#include "ParticleObject.h"

class ParticleAffector
{
private:
	//ColorAffector(StartColor,EndColor)
	Color m_startColor;
	Color m_endColor;
	int m_life;

	//RotateAffector
	float m_rotation;

	//ScaleAffector
	float m_scale;

	//GravityAffector
	Vector m_gravity;

public:
	ParticleAffector();
	ParticleAffector(Color start,Color end, float r, float s, Vector g);
	float Lerp(float current, float start, float end);
	void update(ParticleObject* po);
};