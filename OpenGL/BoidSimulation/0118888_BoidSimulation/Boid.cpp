#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Boid.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 1000
#define PI 3.141592635

Boid::Boid(float x, float y)
{
	acceleration = Vector2(0, 0);
	velocity = Vector2(rand() % 3 - 2, rand() % 3 - 2);
	pos = Vector2(x, y);
	maxSpeed = 8.0;
	maxForce = 0.5;
	glGenTextures(TEXTURE_COUNT, mTextureID);
	loadTexture("../media/boid.bmp", mTextureID[0]);
}

void Boid::applyForce(Vector2 force)
{
	acceleration.addVector(force);
}

void Boid::loadTexture(const char* path, GLuint textureID)
{
	CBitmap bitmap(path);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());
}

Vector2 Boid::Separation(vector<Boid> boids)
{
	float desiredseparation = 20;
	Vector2 steer(0, 0);
	int count = 0;
	for (int i = 0; i < boids.size(); i++) 
	{		
		float d = pos.distance(boids[i].pos);
		if ((d > 0) && (d < desiredseparation)) 
		{
			Vector2 diff(0, 0);
			diff = diff.subTwoVector(pos, boids[i].pos);
			diff.normalize();
			diff.divScalar(d);
			steer.addVector(diff);
			count++;
		}	
	}
	if (count > 0)
	{
		steer.divScalar((float)count);
	}
		
	if (steer.magnitude() > 0) 
	{
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}

Vector2 Boid::Alignment(vector<Boid> Boids)
{
	float neighbordist = 50;

	Vector2 sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++) 
	{
		float d = pos.distance(Boids[i].pos);
		if ((d > 0) && (d < neighbordist)) 
		{
			sum.addVector(Boids[i].velocity);
			count++;
		}
	}
	if (count > 0) 
	{
		sum.divScalar((float)count);
		sum.normalize();            
		sum.mulScalar(maxSpeed);    
									
		Vector2 steer;
		steer = steer.subTwoVector(sum, velocity); 
		steer.limit(maxForce);
		return steer;
	}
	else
	{
		Vector2 temp(0, 0);
		return temp;
	}
}

Vector2 Boid::Cohesion(vector<Boid> Boids)
{
	float neighbordist = 50;
	Vector2 sum(0, 0);
	int count = 0;
	for (int i = 0; i < Boids.size(); i++) 
	{
		float d = pos.distance(Boids[i].pos);
		if ((d > 0) && (d < neighbordist)) 
		{
			sum.addVector(Boids[i].pos);
			count++;
		}
	}
	if (count > 0) {
		sum.divScalar(count);
		return seek(sum);
	}
	else {
		Vector2 temp(0, 0);
		return temp;
	}
}

Vector2 Boid::Attraction(vector<Attractor> attractor)
{
	float attractist = 1000;
	Vector2 steer(0, 0);
	int count = 0;
	for (int i = 0; i < attractor.size(); i++) {
		float d = pos.distance(attractor[i].pos);
		if ((d > 0) && (d < attractist)) {
			Vector2 diff(0, 0);
			diff = diff.subTwoVector(attractor[i].pos,pos);
			diff.mulScalar(0.02);
			steer.addVector(diff);
			count++;
		}
	}
	if (count > 0)
	{
		steer.divScalar((float)count);
	}
	if (steer.magnitude() > 0)
	{
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}

Vector2 Boid::Repell(vector<Repeller> Repeller)
{
	float desiredseparation = 20;
	Vector2 steer(0, 0);
	int count = 0;
	for (int i = 0; i < Repeller.size(); i++) 
	{
		float d = pos.distance(Repeller[i].pos);		
		if((d > 0) && (d < desiredseparation))
		{
			Vector2 diff(0, 0);
			diff = diff.subTwoVector(pos, Repeller[i].pos);
			//diff.normalize();
			diff.mulScalar(0.2);
			steer.addVector(diff);
			count++;
		}
	}
	if (count > 0)
	{
		steer.divScalar((float)count);
	}
	if (steer.magnitude() > 0)
	{
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(velocity);
		steer.limit(maxForce);
	}
	return steer;
}

Vector2 Boid::seek(Vector2 v)
{
	Vector2 desired;
	desired.subVector(v); 
	desired.normalize();
	desired.mulScalar(maxSpeed);
	acceleration.subTwoVector(desired, velocity);
	acceleration.limit(maxForce);
	return acceleration;
}

void Boid::update()
{
	acceleration.mulScalar(.4);
	velocity.addVector(acceleration);
	velocity.limit(maxSpeed);
	pos.addVector(velocity);
	acceleration.mulScalar(0);
}

void Boid::draw()
{	
	glBindTexture(GL_TEXTURE_2D, mTextureID[0]);
	glBegin(GL_TRIANGLES);								// Drawing Using Triangle
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f + pos.x, -5.0f + pos.y, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f + pos.x, -5.0f + pos.y, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f + pos.x, 5.0f + pos.y, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f + pos.x, 5.0f + pos.y, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f + pos.x, 5.0f + pos.y, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f + pos.x, -5.0f + pos.y, 0.0f);
	glEnd();	
}

void Boid::run(vector <Boid> v, vector<Attractor> a, vector<Repeller> r)
{
	flock(v,a,r);
	update();
	borders();
	draw();
}

void Boid::flock(vector<Boid> v, vector<Attractor> a, vector<Repeller> r)
{
	Vector2 sep = Separation(v);
	Vector2 ali = Alignment(v);
	Vector2 coh = Cohesion(v);
	Vector2 atr = Attraction(a);
	Vector2 rep = Repell(r);
	// Arbitrarily weight these forces
	sep.mulScalar(1.5);
	ali.mulScalar(1.0); // Might need to alter weights for different characteristics
	coh.mulScalar(1.0);
	atr.mulScalar(1.0);
	rep.mulScalar(5.0);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
	applyForce(atr);
	applyForce(rep);
}

void Boid::borders()
{
	if (pos.x < 0)    pos.x += WINDOW_WIDTH;
	if (pos.y < 0)    pos.y += WINDOW_HEIGHT;
	if (pos.x > 1000) pos.x -= WINDOW_WIDTH;
	if (pos.y > 600) pos.y -= WINDOW_HEIGHT;
}

float Boid::angle(Vector2 v)
{
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}
