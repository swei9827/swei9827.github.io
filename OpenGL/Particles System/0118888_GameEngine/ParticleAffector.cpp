#include "ParticleAffector.h"

ParticleAffector::ParticleAffector()
{
	m_startColor = Color(0.5f,0.0f,0.5f);
	m_endColor = Color(1.0f,1.0f,0.0f);
	m_rotation = 100.0f;
	m_scale = 0.10f;
	m_gravity = Vector(0.0f,-0.005f,0.0f);
	m_life = 100;
}

ParticleAffector::ParticleAffector(Color start, Color end, float r, float s, Vector g)
{
	m_startColor = start;
	m_endColor = end;
	m_rotation = r;
	m_scale = s;
	m_gravity = g;
}

float ParticleAffector::Lerp(float current, float start, float end)
{
	return (1 - current)*start + current * end;
}

void ParticleAffector::update(ParticleObject* po)
{
	float current = po->getLife() / m_life;
	
	//color
	Color temp = Color();
	temp.r = Lerp(current, m_startColor.r, m_endColor.r);
	temp.g = Lerp(current, m_startColor.g, m_endColor.g);
	temp.b = Lerp(current, m_startColor.b, m_endColor.b);
	po->setColor(temp);

	//rotate
	float newRotation = m_rotation/m_life;
	po->setRotation(po->getRotation()+newRotation);

	//scale
	float newScale = m_scale / m_life;
	po->setScale(po->getScale() - newScale);

	//gravity
	po->setAcceleration(po->getAcceleration() + m_gravity);

}