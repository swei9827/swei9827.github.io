#ifndef _GAMEOFLIFE_H
#define _GAMEOFLIFE_H

#include "demo_base.h"
#include "Bitmap.h"

#define TEXTURE_COUNT 4

class GameOfLife : public DemoBase
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
	int m;
	int n;
	int box_size;
	bool *state;
	bool isPlay;
	bool board1;

	void init()
	{
		glGenTextures(TEXTURE_COUNT, mTextureID);
		loadTexture("../media/play.bmp", mTextureID[0]);
		loadTexture("../media/clear.bmp", mTextureID[1]);
		loadTexture("../media/size.bmp", mTextureID[2]);
		loadTexture("../media/speed.bmp", mTextureID[3]);
		m = 35;
		n = 60;
		box_size = 10;
		isPlay = false;
		board1 = true;

		state = new bool[m * n];
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < m; i++)
			{
				state[i + j * m] = false;
			}
		}
	}

	void deinit()
	{

	}

	void Select(int m, int n, bool state[], int i, int j)
	{
		state[i + j * m] = true;
	}

	void Deselect(int m, int n, bool state[], int i, int j)
	{
		state[i + j * m] = false;
	}

	void Clear()
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				state[i + j * m] = false;
			}
		}
	}

	void drawPlay()
	{
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);

		glBegin(GL_TRIANGLES);								// Drawing Using Triangle
		glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -40.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(50.0f, -40.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, -10.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(50.0f, -10.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(10.0f, -10.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0f, -40.0f, 0.0f);
		glEnd();
	}

	void drawClear()
	{
		glBindTexture(GL_TEXTURE_2D, mTextureID[1]);

		glBegin(GL_TRIANGLES);								// Drawing Using Triangle
		glTexCoord2f(0.0f, 0.0f); glVertex3f(60.0f, -40.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(100.0f, -40.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0f, -10.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0f, -10.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(60.0f, -10.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(60.0f, -40.0f, 0.0f);
		glEnd();
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

	void drawSpeed()
	{
		glBindTexture(GL_TEXTURE_2D, mTextureID[3]);

		glBegin(GL_TRIANGLES);								// Drawing Using Triangle
		glTexCoord2f(0.0f, 0.0f); glVertex3f(160.0f, -40.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(200.0f, -40.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(200.0f, -10.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(200.0f, -10.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(160.0f, -10.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(160.0f, -40.0f, 0.0f);
		glEnd();
	}

	void state_update(int m, int n, bool state[])
	{
		bool *state_new;
		int i;
		int im;
		int ip;
		int j;
		int jm;
		int jp;
		int neighbors;

		state_new = new bool[m*n];

		for (j = 0; j < n; j++)
		{
			for (i = 0; i < m; i++)
			{
				neighbors = 0;
				if (0 < i && 0 < j)
				{
					neighbors = neighbors + (int)state[(i - 1) + (j - 1)*m];
				}
				if (0 < i)
				{
					neighbors = neighbors + (int)state[(i - 1) + (j)*m];
				}
				if (0 < i && j < n - 1)
				{
					neighbors = neighbors + (int)state[(i - 1) + (j + 1)*m];
				}
				if (0 < j)
				{
					neighbors = neighbors + (int)state[(i)+(j - 1)*m];
				}
				if (j < n - 1)
				{
					neighbors = neighbors + (int)state[(i)+(j + 1)*m];
				}
				if (i < m - 1 && 0 < j)
				{
					neighbors = neighbors + (int)state[(i + 1) + (j - 1)*m];
				}
				if (i < m - 1)
				{
					neighbors = neighbors + (int)state[(i + 1) + (j)*m];
				}
				if (i < m - 1 && j < n - 1)
				{
					neighbors = neighbors + (int)state[(i + 1) + (j + 1)*m];
				}

				if (neighbors == 3)
				{
					state_new[i + j * m] = true;
				}
				else if (neighbors == 2)
				{
					state_new[i + j * m] = state[i + j * m];
				}
				else
				{
					state_new[i + j * m] = false;
				}
			}
		}
		//
		//  Update.
		//
		for (j = 0; j < n; j++)
		{
			for (i = 0; i < m; i++)
			{
				state[i + j * m] = state_new[i + j * m];
			}
		}

		delete[] state_new;

		return;
	}

	void box_draw(int i, int j, bool state_ij)
	{
		float p[2];
		GLfloat a;
		GLfloat b;
		GLfloat c;

		GLfloat gray[3] = { 0.8, 0.8, 0.8 };
		GLfloat black[3] = { 0.0, 0.0, 0.0 };

		if (state_ij)
		{
			glColor3fv(black);
		}
		else
		{
			glColor3fv(gray);
		}

		c = box_size;
		a = j * c;
		b = (m - 1 - i) * c;

		glBegin(GL_POLYGON);
		p[0] = a + 1;
		p[1] = b + 1;
		glVertex2fv(p);
		p[0] = a + c - 1;
		p[1] = b + 1;
		glVertex2fv(p);
		p[0] = a + c - 1;
		p[1] = b + c - 1;
		glVertex2fv(p);
		p[0] = a + 1;
		p[1] = b + c - 1;
		glVertex2fv(p);
		glEnd();
		glFlush();
	}

	void draw()
	{
		glEnable(GL_TEXTURE_2D); // enable texturing
		if (isPlay)
		{
			state_update(m, n, state);
		}
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < m; i++)
			{
				box_draw(i, j, state[i + j * m]);
			}
		}
		
		drawPlay();
		drawClear();
		drawSize();
		drawSpeed();
		glDisable(GL_TEXTURE_2D);
	}
};

#endif