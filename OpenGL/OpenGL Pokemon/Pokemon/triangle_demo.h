#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include "demo_base.h"

class TriangleDemo : public DemoBase
{
private:
	float m_translation;
	float m_rotation;
	float wink_speed;
public:
	void init()
	{
	}

	void deinit()
	{
	}

	void drawAxis(const Matrix& viewMatrix)
	{
	// ============draw axis.
		glLoadMatrixf((GLfloat*)viewMatrix.mVal);
		glBegin(GL_LINES);
			glColor3f(1.0f, 0.3f, 0.3f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(1.0f, 0.0f, 0.0f);

			glColor3f(0.3f, 1.0f, 0.3f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 1.0f, 0.0f);

			glColor3f(0.3f, 0.3f, 1.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 1.0f);
		glEnd();
		// ============================
	}
	
	void drawCube(float startX, float startY, float startZ,float x,float y,float z)
	{
		glBegin(GL_TRIANGLES);
		//1
		glColor3f(0.137255f, 0.556863f, 0.419608f);
		glVertex3f(x+startX , y+startY, z+startZ);
		glVertex3f(-x + startX, y + startY, z + startZ);
		glVertex3f(x + startX, -y + startY, z + startZ);

		glVertex3f(-x + startX, -y + startY, z + startZ);
		glVertex3f(-x + startX, y + startY, z + startZ);
		glVertex3f(x + startX, -y + startY, z + startZ);
		//2
		glVertex3f(x + startX, y + startY, -z + startZ);
		glVertex3f(-x + startX, y + startY, -z + startZ);
		glVertex3f(x + startX, -y + startY, -z + startZ);

		glVertex3f(-x + startX, y + startY, z + startZ);//
		glVertex3f(-x + startX, y + startY, -z + startZ);
		glVertex3f(x + startX, -y + startY, -z + startZ);
		//3
		glVertex3f(x + startX, y + startY, -z + startZ);
		glVertex3f(x + startX, y + startY, z + startZ);
		glVertex3f(-x + startX, y + startY, z + startZ);

		glVertex3f(-x + startX, y + startY, z + startZ);
		glVertex3f(x + startX, y + startY, -z + startZ);
		glVertex3f(-x + startX, y + startY, -z + startZ);
		//4
		glVertex3f(x + startX, -y + startY, -z + startZ);
		glVertex3f(x + startX, -y + startY, z + startZ);
		glVertex3f(-x + startX, -y + startY, z + startZ);

		glVertex3f(-x + startX, -y + startY, z + startZ);
		glVertex3f(x + startX, -y + startY, -z + startZ);
		glVertex3f(-x + startX, -y + startY, -z + startZ);
		//5
		glVertex3f(x + startX, y + startY, -z + startZ);
		glVertex3f(x + startX, y + startY, z + startZ);
		glVertex3f(x + startX, -y + startY, z + startZ);

		glVertex3f(x + startX, -y + startY, z + startZ);
		glVertex3f(x + startX, y + startY, -z + startZ);
		glVertex3f(x + startX, -y + startY, -z + startZ);
		//6
		glVertex3f(-x + startX, y + startY, -z + startZ);
		glVertex3f(-x + startX, y + startY, z + startZ);
		glVertex3f(-x + startX, -y + startY, z + startZ);

		glVertex3f(-x + startX, -y + startY, z + startZ);
		glVertex3f(-x + startX, y + startY, -z + startZ);
		glVertex3f(-x + startX, -y + startY, -z + startZ);
		glEnd();
	}

	void drawPyramid(void)
	{
		//btm
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);

		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		//wall1
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		//wall2
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		//wall3
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		//wall4
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glEnd();
	}
	void drawCylinder(float h,float startingX,float startingY,float startingZ,float r,float g,float b)
	{
		float height = h;
		int sides = 120;
		float radius = 1.0f;

		glBegin(GL_TRIANGLES);
		glColor3f(r, g, b);
		for (int i = 1; i <= sides; i++)
		{
			float theta = i * M_2PI / sides;
			float theta2 = (i+1) * M_2PI / sides;
			float x = cos(theta) * radius;
			float y = sin(theta) * radius;
			float x2 = cos(theta2) * radius;
			float y2 = sin(theta2) * radius;
			glVertex3f(x+startingX, height + startingY, y + startingZ);
			glVertex3f(0.0f + startingX, height + startingY, 0.0f + startingZ);
			glVertex3f(x2+startingX, height + startingY,y2 + startingZ);

			glVertex3f(x + startingX, 0.0f + startingY,y + startingZ);
			glVertex3f(0.0f + startingX, 0.0f + startingY, 0.0f + startingZ);
			glVertex3f(x2 + startingX, 0.0f + startingY, y2 + startingZ);

			glVertex3f(x +startingX, height + startingY, y + startingZ);
			glVertex3f(x2 + startingX, height + startingY, y2 + startingZ);
			glVertex3f(x + startingX, 0.0f + startingY, y + startingZ);

			glVertex3f(x + startingX, 0.0f + startingY, y + startingZ);
			glVertex3f(x2 + startingX, 0.0f + startingY, y2 + startingZ);
			glVertex3f(x2 + startingX, height + startingY, y2 + startingZ);
		}
		glEnd();
	}

	void drawSphere(float radius, int divO, int divA,float startX,float startY, float startZ,float r, float g, float b)
	{
		//glTranslatef(0.0f, 1.5f, 2.0f);
		float px, py, pz;


		glBegin(GL_TRIANGLES);

		for (int i = 0; i <= divO; i++)
		{

			float tempFloat = i * 0.005f;
			if (i >= divO / 2)
			{
				tempFloat = (divO - i)* 0.005f;
			}

			for (int j = 0; j <= divA; j++)
			{
				float theta = float(i) / divO * 2.0* M_PI;
				float nextTheta = (float(i) + 1) / divO * 2.0 * M_PI;

				float tempta = float(j) / divA * M_PI;
				float tempnextta = (float(j) + 1) / divA * M_PI;

				//glColor3f(0.33f - tempFloat, 0.57f - tempFloat, 0.75f - tempFloat);
				glColor3f(r, g, b);
				pz = cos(tempta)*radius;
				py = sin(tempta)*sin(theta)*radius;
				px = sin(tempta)*cos(theta)*radius;

				glVertex3f(px + startX, py + startY, pz + startZ);

				pz = cos(tempta)*radius;
				py = sin(tempta)*sin(nextTheta)*radius;
				px = sin(tempta)*cos(nextTheta)*radius;

				glVertex3f(px + startX, py + startY, pz + startZ);

				pz = cos(tempnextta)*radius;
				py = sin(tempnextta)*sin(theta)*radius;
				px = sin(tempnextta)*cos(theta)*radius;

				glVertex3f(px + startX, py + startY, pz + startZ);
				///////////
				pz = cos(tempnextta)*radius;
				py = sin(tempnextta)*sin(theta)*radius;
				px = sin(tempnextta)*cos(theta)*radius;

				glVertex3f(px + startX, py + startY, pz + startZ);

				pz = cos(tempta)*radius;
				py = sin(tempta)*sin(nextTheta)*radius;
				px = sin(tempta)*cos(nextTheta)*radius;

				glVertex3f(px + startX, py + startY, pz + startZ);

				pz = cos(tempnextta)*radius;
				py = sin(tempnextta)*sin(nextTheta)*radius;
				px = sin(tempnextta)*cos(nextTheta)*radius;

				glVertex3f(px + startX, py + startY, pz + startZ);
			}
		}
		glEnd();
	}

	void drawOvoide(float radius, int divO, int divA, float startX, float startY, float startZ, float r, float g, float b,bool isHori, float l)
	{
		//glTranslatef(0.0f, 1.5f, 2.0f);
		float px, py, pz;


		glBegin(GL_TRIANGLES);
		if (isHori)
		{
			for (int i = 0; i <= divO; i++)
			{

				float tempFloat = i * 0.005f;
				if (i >= divO / 2)
				{
					tempFloat = (divO - i)* 0.005f;
				}

				for (int j = 0; j <= divA; j++)
				{
					float theta = float(i) / divO * 2.0* M_PI;
					float nextTheta = (float(i) + 1) / divO * 2.0 * M_PI;

					float tempta = float(j) / divA * M_PI;
					float tempnextta = (float(j) + 1) / divA * M_PI;

					//glColor3f(0.33f - tempFloat, 0.57f - tempFloat, 0.75f - tempFloat);
					glColor3f(r, g, b);
					pz = cos(tempta)*radius;
					py = sin(tempta)*sin(theta)*radius;
					px = sin(tempta)*cos(theta)*radius;

					glVertex3f(px * l + startX, py + startY, pz + startZ);

					pz = cos(tempta)*radius;
					py = sin(tempta)*sin(nextTheta)*radius;
					px = sin(tempta)*cos(nextTheta)*radius;

					glVertex3f(px * l + startX, py + startY, pz + startZ);

					pz = cos(tempnextta)*radius;
					py = sin(tempnextta)*sin(theta)*radius;
					px = sin(tempnextta)*cos(theta)*radius;

					glVertex3f(px * l + startX, py + startY, pz + startZ);
					///////////
					pz = cos(tempnextta)*radius;
					py = sin(tempnextta)*sin(theta)*radius;
					px = sin(tempnextta)*cos(theta)*radius;

					glVertex3f(px * l + startX, py + startY, pz + startZ);

					pz = cos(tempta)*radius;
					py = sin(tempta)*sin(nextTheta)*radius;
					px = sin(tempta)*cos(nextTheta)*radius;

					glVertex3f(px * l + startX, py + startY, pz + startZ);

					pz = cos(tempnextta)*radius;
					py = sin(tempnextta)*sin(nextTheta)*radius;
					px = sin(tempnextta)*cos(nextTheta)*radius;

					glVertex3f(px * l + startX, py + startY, pz + startZ);
				}
			}
		}
		else
		{
			for (int i = 0; i <= divO; i++)
			{

				float tempFloat = i * 0.005f;
				if (i >= divO / 2)
				{
					tempFloat = (divO - i)* 0.005f;
				}

				for (int j = 0; j <= divA; j++)
				{
					float theta = float(i) / divO * 2.0* M_PI;
					float nextTheta = (float(i) + 1) / divO * 2.0 * M_PI;

					float tempta = float(j) / divA * M_PI;
					float tempnextta = (float(j) + 1) / divA * M_PI;

					//glColor3f(0.33f - tempFloat, 0.57f - tempFloat, 0.75f - tempFloat);
					glColor3f(r, g, b);
					pz = cos(tempta)*radius;
					py = sin(tempta)*sin(theta)*radius;
					px = sin(tempta)*cos(theta)*radius;

					glVertex3f(px + startX, py * l + startY, pz + startZ);

					pz = cos(tempta)*radius;
					py = sin(tempta)*sin(nextTheta)*radius;
					px = sin(tempta)*cos(nextTheta)*radius;

					glVertex3f(px + startX, py * l + startY, pz + startZ);

					pz = cos(tempnextta)*radius;
					py = sin(tempnextta)*sin(theta)*radius;
					px = sin(tempnextta)*cos(theta)*radius;

					glVertex3f(px + startX, py * l + startY, pz + startZ);
					///////////
					pz = cos(tempnextta)*radius;
					py = sin(tempnextta)*sin(theta)*radius;
					px = sin(tempnextta)*cos(theta)*radius;

					glVertex3f(px + startX, py * l + startY, pz + startZ);

					pz = cos(tempta)*radius;
					py = sin(tempta)*sin(nextTheta)*radius;
					px = sin(tempta)*cos(nextTheta)*radius;

					glVertex3f(px + startX, py * l + startY, pz + startZ);

					pz = cos(tempnextta)*radius;
					py = sin(tempnextta)*sin(nextTheta)*radius;
					px = sin(tempnextta)*cos(nextTheta)*radius;

					glVertex3f(px + startX, py * l + startY, pz + startZ);
				}
			}
		}
		glEnd();
	}

	void drawBottom()
	{
		//top
		glBegin(GL_TRIANGLES);
		glColor3f(0.6f, 0.29803921568f, 0.0f);
		glVertex3f(3.5f, -3.0f, -3.5f);
		glVertex3f(-3.5f, -3.0f, 3.5f);
		glVertex3f(3.5f, -3.0f, 3.5f);

		glVertex3f(-3.5f, -3.0f, -3.5f);
		glVertex3f(-3.5f, -3.0f, 3.5f);
		glVertex3f(3.5f, -3.0f, -3.5f);
		//wall1
		glColor3f(0.4f, 0.2f, 0.0f);
		glVertex3f(3.5f, -3.0f, 3.5f);
		glVertex3f(-3.5f, -3.0f, 3.5f);
		glVertex3f(0.0f, -6.0f, 0.0f);
		//wall2
		glVertex3f(3.5f, -3.0f, -3.5f);
		glVertex3f(-3.5f, -3.0f, -3.5f);
		glVertex3f(0.0f, -6.0f, 0.0f);
		//wall3
		glVertex3f(3.5f, -3.0f, 3.5f);
		glVertex3f(3.5f, -3.0f, -3.5f);
		glVertex3f(0.0f, -6.0f, 0.0f);
		//wall4
		glVertex3f(-3.5f, -3.0f, 3.5f);
		glVertex3f(-3.5f, -3.0f, -3.5f);
		glVertex3f(0.0f, -6.0f, 0.0f);
		glEnd();
	}
	void draw(const Matrix& viewMatrix)
	{
		drawAxis(viewMatrix);

		m_translation += 0.05f;
		m_rotation += 0.04f;
		wink_speed += 0.07f;

		drawBottom();
		//rock
		drawSphere(0.3f, 5, 6, 0.7f, -3.0f, 2.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.4f, 5, 6, 1.1f, -3.0f, 1.4f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.5f, 4, 5, 1.3f, -3.0f, 1.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.3f, 6, 4, -0.4f, -3.0f, 2.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.5f, 4, 7, -1.0f, -3.0f, 1.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.5f, 4, 7, 0.3f, -3.0f, 2.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.5f, 7, 8, -0.7f, -3.0f, 1.7f, 0.7f, 0.29803921568f, 0.0f);
		//behind,right
		drawSphere(0.5f, 8, 4, 1.3f, -3.0f, 0.2f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.3f, 5, 3, 1.7f, -3.0f, 0.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.4f, 6, 6, 2.1f, -3.0f, -0.6f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.5f, 4, 6, 2.3f, -3.0f, -1.0f, 0.7f, 0.29803921568f, 0.0f);
		//behind.left
		drawSphere(0.3f, 6, 4, -1.4f, -3.0f, 0.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.5f, 4, 7, -2.0f, -3.0f, -1.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.5f, 4, 6, -0.9f, -3.0f, 0.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.5f, 7, 8, -1.7f, -3.0f, -0.3f, 0.7f, 0.29803921568f, 0.0f);
		//behind
		drawSphere(0.7f, 5, 3, 1.7f, -3.2f, -1.8f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.8f, 7, 5, 1.2f, -3.2f, -2.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.7f, 4, 4, -1.7f, -3.2f, -1.8f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.8f, 5, 8, -1.2f, -3.2f, -2.0f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.4f, 5, 3, 0.3f, -3.0f, -1.8f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.5f, 7, 5, -0.7f, -3.0f, -1.8f, 0.7f, 0.29803921568f, 0.0f);
		drawSphere(0.4f, 3, 6, -0.1f, -3.0f, -1.7f, 0.7f, 0.29803921568f, 0.0f);


		
		Matrix modelMatrix1 = Matrix::makeTranslationMatrix(Vector(0.0f, sinf(m_translation)*0.2f, 0.0f));
		Matrix viewSpaceMatrix1 = viewMatrix * modelMatrix1;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix1.mVal);
		drawCylinder(3.5f, 1.0f, -3.5f, -1.0f, 0.8f, 0.45f, 0.1f);
		drawSphere(1.0f, 30, 30, 1.0f, 0.0f,-1.0f, 0.8f, 0.45f, 0.1f);
		
		drawOvoide(0.1f, 30, 30, 1.4f, 0.0f, -0.1f, 0.2f, 0.2f, 0.2f,false,cosf(wink_speed)*1.6);
		drawOvoide(0.1f, 30, 30, 0.6f, 0.0f, -0.1f, 0.2f, 0.2f, 0.2f, false, cosf(wink_speed)*1.6);
		drawOvoide(0.2f, 30, 30, 1.0f, -0.5f, 0.0f, 0.97f, 0.23f, 0.325f, true, 1.8f);

		
		Matrix modelMatrix2 = Matrix::makeTranslationMatrix(Vector(0.0f, cosf(m_translation)*0.2f, 0.0f));
		Matrix viewSpaceMatrix2 = viewMatrix * modelMatrix2;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix2.mVal);
		drawCylinder(2.5f, 0.0f, -3.5f, 1.0f, 0.8f, 0.43f, 0.1f);
		drawSphere(1.0f, 30, 30, 0.0f, -1.0f, 1.0f, 0.8f, 0.43f, 0.1f);
		drawOvoide(0.1f, 30, 30, 0.4f, -1.0f, 1.9f, 0.2f, 0.2f, 0.2f, false, 1.6f);
		drawOvoide(0.1f, 30, 30, -0.4f, -1.0f, 1.9f, 0.2f, 0.2f, 0.2f, false, 1.6f);
		drawOvoide(0.2f, 30, 30, 0.0f, -1.5f, 2.0f, 0.97f, 0.23f, 0.325f, true, 1.8f);
		
		Matrix modelMatrix3 = Matrix::makeTranslationMatrix(Vector(0.0f, cosf(m_translation)*0.34f, 0.0f));
		Matrix viewSpaceMatrix3 = viewMatrix * modelMatrix3;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix3.mVal);
		drawCylinder(4.5f, -1.0f, -3.5f, -1.0f, 0.8f, 0.47f, 0.1f);
		drawSphere(1.0f, 30, 30, -1.0f, 1.0f, -1.0f, 0.8f, 0.47f, 0.1f);
		drawOvoide(0.1f, 30, 30, -1.4f, 1.0f, -0.1f, 0.2f, 0.2f, 0.2f, false, cosf(wink_speed)*1.6);
		drawOvoide(0.1f, 30, 30, -0.6f, 1.0f, -0.1f, 0.2f, 0.2f, 0.2f, false, cosf(wink_speed)*1.6);
		drawOvoide(0.2f, 30, 30, -1.0f, 0.5f, 0.0f, 0.97f, 0.23f, 0.325f, true, 1.8f);
		
		Matrix translate3 = Matrix::makeTranslationMatrix(Vector(cosf(m_rotation)*3.0f, 0.0f, sinf(m_rotation)*10.0f));		
		

		//========================================================================
		//enable wireframe mode
		//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

		//grass
		for (int i = 0; i <6; i++)
		{
			Matrix modelMatrix = Matrix::makeTranslationMatrix(cosf(m_translation)*i*0.1,0.0f, 0.0f); //* Matrix::makeTranslationMatrix(6.0f, 0.0f, 0.0f);
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawCube(2, 0.2*i-3,3,0.1,0.1,0.1);
		}
		for (int i = 0; i <6; i++)
		{
			Matrix modelMatrix = Matrix::makeTranslationMatrix(sinf(m_translation*0.8f)*i*0.1f, 0.0f, 0.0f); //* Matrix::makeTranslationMatrix(6.0f, 0.0f, 0.0f);
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawCube(2, 0.2*i-3, 3, 0.1, 0.1, 0.1);
		}
		for (int i = 0; i <6; i++)
		{
			Matrix modelMatrix = Matrix::makeTranslationMatrix(0.0f, 0.0f, i*0.1) * Matrix::makeTranslationMatrix(cosf(m_translation*0.9f)*i*0.1f, 0.0f, 0.0f);
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawCube(2, 0.2*i-3, 3, 0.1, 0.1, 0.1);
		}
		for (int i = 0; i <6; i++)
		{
			Matrix modelMatrix = Matrix::makeTranslationMatrix(0.0f, 0.0f, i*-0.1) * Matrix::makeTranslationMatrix(sinf(m_translation*0.7f)*i*0.1f, 0.0f, 0.0f);
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawCube(2, 0.2*i - 3, 3, 0.1, 0.1, 0.1);
		}
		//grass2
		for (int i = 0; i <6; i++)
		{
			Matrix modelMatrix = Matrix::makeTranslationMatrix(cosf(m_translation)*i*0.1, 0.0f, 0.0f); //* Matrix::makeTranslationMatrix(6.0f, 0.0f, 0.0f);
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawCube(-2.1, 0.2*i - 3, 2.7, 0.1, 0.1, 0.1);
		}
		for (int i = 0; i <6; i++)
		{
			Matrix modelMatrix = Matrix::makeTranslationMatrix(sinf(m_translation*0.8f)*i*0.1f, 0.0f, 0.0f); //* Matrix::makeTranslationMatrix(6.0f, 0.0f, 0.0f);
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawCube(-2.1, 0.2*i - 3, 2.7, 0.1, 0.1, 0.1);
		}
		for (int i = 0; i <6; i++)
		{
			Matrix modelMatrix = Matrix::makeTranslationMatrix(0.0f, 0.0f, i*0.1) * Matrix::makeTranslationMatrix(cosf(m_translation*0.9f)*i*0.1f, 0.0f, 0.0f);
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawCube(-2.1, 0.2*i - 3, 2.7, 0.1, 0.1, 0.1);
		}
		for (int i = 0; i <6; i++)
		{
			Matrix modelMatrix = Matrix::makeTranslationMatrix(0.0f, 0.0f, i*-0.1) * Matrix::makeTranslationMatrix(sinf(m_translation*0.7f)*i*0.1f, 0.0f, 0.0f);
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawCube(-2.1, 0.2*i - 3, 2.7, 0.1, 0.1, 0.1);
		}
	}
};

#endif
