#include <math.h>
#include "Vector2.h"

#define PI 3.141592635

void Vector2::set(float i, float o)
{
	x = i;
	y = o;
}

void Vector2::addVector(Vector2 v)
{
	x += v.x;
	y += v.y;
}

void Vector2::addScalar(float s)
{
	x += s;
	y += s;
}

void Vector2::subVector(Vector2 v)
{
	x -= v.x;
	y -= v.y;
}

Vector2 Vector2::subTwoVector(Vector2 v, Vector2 v2)
{
	Vector2 tmp;
	v.x -= v2.x;
	v.y -= v2.y;
	tmp.set(v.x, v.y);
	return tmp;
}

void Vector2::subScalar(float s)
{
	x -= s;
	y -= s;
}

void Vector2::mulVector(Vector2 v)
{
	x *= v.x;
	y *= v.y;
}

void Vector2::mulScalar(float s)
{
	x *= s;
	y *= s;
}

void Vector2::divVector(Vector2 v)
{
	x /= v.x;
	y /= v.y;
}

void Vector2::divScalar(float s)
{
	x /= s;
	y /= s;
}

void Vector2::limit(double max)
{
	double size = magnitude();

	if (size > max) {
		set(x / size, y / size);
	}
}

float Vector2::distance(Vector2 v)
{
	float dx = x - v.x;
	float dy = y - v.y;
	float dist = sqrt(dx*dx + dy * dy);
	return dist;
}

float Vector2::dotProduct(Vector2 v)
{
	float dot = x * v.x + y * v.y;
	return dot;
}

float Vector2::magnitude()
{
	return sqrt(x*x + y * y);
}

void Vector2::setMagnitude(float x)
{
	normalize();
	mulScalar(x);
}

float Vector2::angleBetween(Vector2 v)
{
	if (x == 0 && y == 0) return 0.0f;
	if (v.x == 0 && v.y == 0) return 0.0f;

	double dot = x * v.x + y * v.y;
	double v1mag = sqrt(x * x + y * y);
	double v2mag = sqrt(v.x * v.x + v.y * v.y);
	double amt = dot / (v1mag * v2mag); 

	if (amt <= -1) {
		return PI;
	}
	else if (amt >= 1) {
		return 0;
	}
	float tmp = acos(amt);
	return tmp;
}

void Vector2::normalize()
{
	float m = magnitude();

	if (m > 0) {
		set(x / m, y / m);
	}
	else {
		set(x, y);
	}
}
