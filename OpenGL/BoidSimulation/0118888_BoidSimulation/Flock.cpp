#include "Boid.h"
#include "Flock.h"

int Flock::getSize()
{
	return boids.size();
}

Boid Flock::getBoid(int i)
{
	return boids[i];
}

void Flock::addBoid(Boid b)
{
	boids.push_back(b);
}

Attractor Flock::getAttractor(int i)
{
	return attractor[i];
}

void Flock::addAttractor(Attractor a)
{
	attractor.push_back(a);
}

Repeller Flock::getRepeller(int i)
{
	return repeller[i];
}

void Flock::addRepeller(Repeller r)
{
	repeller.push_back(r);
}

void Flock::flocking()
{
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < boids.size(); i++)
	{
		boids[i].run(boids, attractor, repeller);
	}
	glDisable(GL_TEXTURE_2D);
}

void Flock::drawObject()
{
	if (attractor.size() > 0)
	{
		for (int i = 0; i < attractor.size(); i++)
		{
			attractor[i].draw();
		}
	}
	if (repeller.size() > 0)
	{
		for (int i = 0; i < repeller.size(); i++)
		{
			repeller[i].draw();
		}
	}
}