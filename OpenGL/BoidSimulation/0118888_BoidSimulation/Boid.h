#ifndef _BOID_H
#define _BOID_H

#pragma once

#include "windows.h"
#include "Vector2.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "GLFW/glfw3.h"
#include "Bitmap.h"
#include "Attractor.h"
#include "Repeller.h"

#define TEXTURE_COUNT 1

class Boid
{
public:
	GLuint mTextureID[TEXTURE_COUNT];
	void loadTexture(const char* path, GLuint textureID);

	Vector2 pos;
	Vector2 velocity;
	Vector2 acceleration;
	float maxSpeed;
	float maxForce;

	Boid() {}
	Boid(float x, float y);
	
	void applyForce(Vector2 force);
	
	Vector2 Separation(vector<Boid> Boids);
	Vector2 Alignment(vector<Boid> Boids);
	Vector2 Cohesion(vector<Boid> Boids);
	Vector2 Attraction(vector<Attractor> Attractor);
	Vector2 Repell(vector<Repeller> Repeller);
	
	Vector2 seek(Vector2 v);
	void run(vector <Boid> v, vector<Attractor> a, vector<Repeller> r);
	void update();
	void flock(vector <Boid> v, vector<Attractor> a,vector<Repeller> r);
	void borders();
	void draw();
	float angle(Vector2 v);
};
#endif
