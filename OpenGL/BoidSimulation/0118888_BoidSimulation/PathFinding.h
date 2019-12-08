#ifndef _PATHFINDING_H
#define _PATHFINDING_H

#include "demo_base.h"
#include "Bitmap.h"
#include "Boid.h"
#include <vector>
#include <array>
#include <stack>
#include <windows.h>

using namespace std;

#define TEXTURE_COUNT 4
#define PLAIN_WIDTH 40
#define PLAIN_HEIGHT 20
#define UNIT 20

class PathFinding : public DemoBase
{
private:
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
public:
	float m_posX;
	float m_posY;
	float maxSpeed;
	Boid* bird[UNIT];

	void init()
	{	
		srand(time(NULL));	
		glGenTextures(TEXTURE_COUNT, mTextureID);
		loadTexture("../media/play.bmp", mTextureID[0]);
		loadTexture("../media/clear.bmp", mTextureID[1]);
		loadTexture("../media/size.bmp", mTextureID[2]);
		loadTexture("../media/speed.bmp", mTextureID[3]);
		maxSpeed = 15.0;
		int randX, randY;
		for (int i = 0; i < UNIT; i++)
		{			
			/*randX = rand() % int((float)2 * maxSpeed) + int(-maxSpeed);
			randY = rand() % int((float)2 * maxSpeed) + int(-maxSpeed);*/
			randX = rand() % 10 - 5;
			randY = rand() %10 -5;
			cout << randX <<"           "<< randY << endl;
			bird[i] = new Boid();
			bird[i]->posX = 700.0;
			bird[i]->posY = 350.0;
			bird[i]->velocityX = i*(float)randX;
			bird[i]->velocityY = i*(float)randY;
			bird[i]->accelerationX = 0.0f;
			bird[i]->accelerationY = 0.0f;
		}
	}		

	void deinit()
	{

	}

	void drawSize()
	{
		glBindTexture(GL_TEXTURE_2D, mTextureID[2]);

		glBegin(GL_TRIANGLES);								// Drawing Using Triangle
		glTexCoord2f(0.0f, 0.0f); glVertex3f(110.0f, -40.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(150.0f, -40.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(150.0f, -10.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(150.0f, -10.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(110.0f, -10.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(110.0f, -40.0f, 0.0f);
		glEnd();
	}

	void drawObject(float x, float y)
	{
		glBindTexture(GL_TEXTURE_2D, mTextureID[3]);

		glBegin(GL_TRIANGLES);								// Drawing Using Triangle
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f + x, 0.0f + y, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(20.0f + x, 0.0f + y, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(20.0f + x, 20.0f + y, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(20.0f + x, 20.0f + y, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f + x, 20.0f + y, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f + x, 0.0f + y, 0.0f);
		glEnd();
	}

	void movement()
	{
		for (int i = 0; i <UNIT; i++)
		{
			if (m_posX > bird[i]->posX)
			{
				bird[i]->accelerationX = (m_posX - bird[i]->posX) / 1280;
			}
			else if (m_posX < bird[i]->posX)
			{
				bird[i]->accelerationX = -((bird[i]->posX - m_posX) / 1280);
			}

			if (m_posY > bird[i]->posY)
			{
				bird[i]->accelerationY = ((m_posY - bird[i]->posY) / 720);
			}
			else if (m_posY < bird[i]->posY)
			{				
				bird[i]->accelerationY = -((bird[i]->posY - m_posY) / 720);
			}
			bird[i]->velocityX += bird[i]->accelerationX ;
			bird[i]->velocityY += bird[i]->accelerationY ;
			if (abs(bird[i]->velocityX) < maxSpeed)
			{
				bird[i]->posX += bird[i]->velocityX;
			}
			else 
			{
				if (bird[i]->velocityX >= 0.0)
				{
					bird[i]->posX += maxSpeed;
				}
				else
				{
					bird[i]->posX += -maxSpeed;
				}
				
			}
			
			if (abs(bird[i]->velocityY) < maxSpeed)
			{
				bird[i]->posY += bird[i]->velocityY;
			}
			else
			{
				if (bird[i]->velocityY >= 0.0)
				{
					bird[i]->posY += maxSpeed;
				}
				else
				{
					bird[i]->posY += -maxSpeed;
				}				
			}			
			//cout << "acceleration x: " << bird[i]->accelerationX*0.1 << "velocity x:" << bird[i]->velocityX << endl;
			drawObject(bird[i]->posX, bird[i]->posY);
		}
	}

	void draw()
	{
		glEnable(GL_TEXTURE_2D); // enable texturing
		glColor3f(1.0f, 1.0f, 1.0f);
		movement();
		glDisable(GL_TEXTURE_2D);
	}
};

#endif