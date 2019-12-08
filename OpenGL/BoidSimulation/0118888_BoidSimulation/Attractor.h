#ifndef _ATTRACTOR_H
#define _ATTRACTOR_H

#pragma once

#include "windows.h"
#include "Vector2.h"
#include <stdlib.h>
#include "GLFW/glfw3.h"
#include "Bitmap.h"

#define TEXTURE_COUNT 1

class Attractor
{
public:
	Vector2 pos;
	float radius;
	GLuint mTextureID[TEXTURE_COUNT];
	
	void loadTexture(const char* path, GLuint textureID)
	{
		CBitmap bitmap(path);

		// Create Linear Filtered Texture
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // apply texture wrapping along horizontal part.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // apply texture wrapping along vertical part.

																	  // bilinear filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // near filtering. (For when texture needs to scale up on screen)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // far filtering. (For when texture need to scale down on screen)

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());
	}

	Attractor(float x, float y)
	{
		pos.x = x;
		pos.y = y;
		glGenTextures(TEXTURE_COUNT, mTextureID);
		loadTexture("../media/attractor.bmp", mTextureID[0]);
	}

	void draw()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);

		glBegin(GL_TRIANGLES);								// Drawing Using Triangle
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f + pos.x, -10.0f + pos.y, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0f + pos.x, -10.0f + pos.y, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f + pos.x, 10.0f + pos.y, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0f + pos.x, 10.0f + pos.y, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0f + pos.x, 10.0f + pos.y, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f + pos.x, -10.0f + pos.y, 0.0f);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
};

#endif
