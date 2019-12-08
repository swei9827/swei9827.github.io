#ifndef VECTOR2_H_
#define VECTOR2_H_
#pragma once
#include <iostream>

using namespace std;

class Vector2
{
public:
	float x;
	float y;

	Vector2()
	{
		x = 0.0;
		y = 0.0;
	}

	Vector2(float xx, float yy)
	{
		x = xx;
		y = yy;
	}

	void set(float x, float y);

	void addVector(Vector2 v);
	void addScalar(float x);

	void subVector(Vector2 v);
	Vector2 subTwoVector(Vector2 v, Vector2 v2);
	void subScalar(float x);

	void mulVector(Vector2 v);
	void mulScalar(float x);

	void divVector(Vector2 v);
	void divScalar(float x);

	void limit(double max);

	float distance(Vector2 v);
	float dotProduct(Vector2 v);
	float magnitude();
	void setMagnitude(float x);
	float angleBetween(Vector2 v);
	void normalize();
};

#endif