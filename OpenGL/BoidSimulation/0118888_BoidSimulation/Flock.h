#include <iostream>
#include <vector>
#include "Boid.h"
#include "Attractor.h"
#include "Repeller.h"

#ifndef FLOCK_H_
#define FLOCK_H_

#pragma once

class Flock {
public:
	vector<Boid> boids;
	vector<Attractor> attractor;
	vector<Repeller> repeller;
	
	Flock() {}
	
	int getSize();
	Boid getBoid(int i);
	void addBoid(Boid b);
	Attractor getAttractor(int i);
	void addAttractor(Attractor a);
	Repeller getRepeller(int i);
	void addRepeller(Repeller r);
		
	void flocking();
	void drawObject();
};

#endif
