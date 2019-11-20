#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Sprite* sprite)
{
	currentTime = 0.0f;
	emissionRate = 0.05f;
	emissionCount = 0.0f;
	m_pSprite = sprite;
	m_emitterShape = EmitterShape::CIRCLE;
	
	ParticleAffector* pAffector = new ParticleAffector();
	m_affectorList.push_back(pAffector);
}

void ParticleSystem::setEmissionRate(float e)
{
	emissionRate = e;
}

void ParticleSystem::setPos(Vector pos)
{
	m_position = pos;
}

Vector ParticleSystem::getPos()
{
	return m_position;
}

void ParticleSystem::addParticle()
{
	ParticleObject* newParticle = new ParticleObject(m_pSprite, 100.0f);

	newParticle->setRotation(float(rand()%360+1));
	newParticle->setPos(Vector(400.0f, 300.0f, 0.0f));
	newParticle->setScale(float(rand()%3+3)/25.0f);

	float speed = 2.5f;
	float x = float(rand() % int(speed * 2) - int(speed));
	float y = float(rand() % int(speed * 2) - int(speed));
	newParticle->setVelocity(Vector(x, y, 0.0));

	setShape(newParticle);

	//spawn particle
	m_particleList.push_back(newParticle);
}

void ParticleSystem::setShape(ParticleObject* po)
{
	if (m_emitterShape == EmitterShape::CIRCLE)
	{
		float radiusLimit = 50.0f;
		float angle = float(rand()%360+1);
		float radius = -radiusLimit * 2 + float(rand() / float(RAND_MAX / (radiusLimit * 4)));
		Vector temp = po->getPos();
		temp.mVal[0] = m_position.mVal[0] + radius * sin(angle);
		temp.mVal[1] = m_position.mVal[1] - radius * cos(angle);
		po->setPos(temp);
		std::cout << "Shape 0" << std::endl;
	}
	else if (m_emitterShape == EmitterShape::POINTSHAPE)
	{
		//default
		std::cout << "Shape 1" << std::endl;
	}
	else if (m_emitterShape == EmitterShape::SQUARE)
	{
		float limit = m_position.mVal[0];
		float x = rand() % int(po->getPos().mVal[0]) + limit - 250;
		float y = rand() % int(po->getPos().mVal[1]) + limit - 350;
		Vector temp = Vector(x, y, 0);
		po->setPos(temp);
		std::cout << "Shape 2" << std::endl;
	}
}

void ParticleSystem::update(float deltaTime)
{
	//check if it;s needed to create new particle(s)
	currentTime += deltaTime;
	if (currentTime >= emissionRate)
	{
		addParticle();
		currentTime = 0.0f;
	}

	//update the particles movement

	std::list<ParticleObject*>::iterator iter = m_particleList.begin();
	while (iter != m_particleList.end())
	{
		ParticleObject* po = *iter;
		if (po->getLife() <= 0)
		{
			iter = m_particleList.erase(iter);
		}
		else
		{
			std::list<ParticleAffector*>::iterator affectiter = m_affectorList.begin();
			while (affectiter != m_affectorList.end())
			{
				ParticleAffector* pa = *affectiter;
				pa->update(po);
				affectiter++;
			}
			po->update();
			++iter;
		}
	}
}

void ParticleSystem::draw(void)
{
	if (m_particleList.size() >= 1)
	{
		std::list<ParticleObject*>::iterator iter = m_particleList.begin();
		while (iter != m_particleList.end())
		{
			ParticleObject* po = *iter;
			po->Draw();
			++iter;
		}
	}
}