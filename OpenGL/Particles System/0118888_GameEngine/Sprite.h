#pragma once
#include <string.h>
#include "GLFW/glfw3.h"
#include "vector.h"
#include "matrix.h"
#include "bitmap.h"

struct Color
{
	float r;
	float g;
	float b;

	Color(float red,float green,float blue)
	{
		r = red;
		g = green;
		b = blue;
	}

	Color()
	{
		r = 1.0f;
		g = 0.0f;
		b = 1.0f;
	}
};

class Sprite
{
private:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_textureID;

public:
	Sprite();
	Sprite(const std::string& file);
	~Sprite();

	GLuint GtextureID;
	void loadTexture(const char* path, GLuint textureID);
	//void draw(float x, float y);

	void draw(float x, float y, float rotation, float scale, const Color &color);
};