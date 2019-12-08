#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>
#include "Vector2.h"

#include "Flock.h"
#include "Boid.h"
#include "Attractor.h"
#include "Repeller.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

using namespace std;

GLFWwindow* window;
Flock flock;
bool isAttractor = false;

void MouseCallback(GLFWwindow* window, int button, int action, int mods);

void onWindowResized(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1;						// Prevent A Divide By Zero By making Height Equal One

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void onMouseMove(GLFWwindow* window, double x, double y)
{
	static int lastX = -1, lastY = -1;
	if (lastX == -1 && lastY == -1)
	{
		lastX = x;
		lastY = y;
		return;
	}

	int offsetX = x - lastX;
	int offsetY = y - lastY;
	lastX = x; lastY = y;

}

int main(int argc, char *argv[])
{
	//glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		return -1;

	// Open an OpenGL window
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Hook window resize.
	glfwSetWindowSizeCallback(window, onWindowResized);
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	// hook mouse move callback and lock/hide mouse cursor.
	glfwSetCursorPosCallback(window, onMouseMove);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSwapInterval(1);

	// initialize OpenGL.
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

														// initialize camera.
														///gCamera.translate(0.0f, 0.0f, 10.0f);
														///Matrix matrix(Matrix::makeIdentityMatrix());
														///Matrix rotateMatrix(Matrix::makeRotateMatrix(0.5f, Vector(0.0f, 1.0f, 0.0f)));
														//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
														
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)WINDOW_WIDTH, 0.0, (double)WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW);

	for (int i = 0; i < 15; i++) {
		Boid b(WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2); 

		flock.addBoid(b);
	}

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSetMouseButtonCallback(window, MouseCallback);

		if (glfwGetKey(window, GLFW_KEY_Z))
		{
			isAttractor = true;
		}
		else if (glfwGetKey(window, GLFW_KEY_X))
		{
			isAttractor = false;
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;

		flock.flocking();
		flock.drawObject();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Vector2 cursorPos(xpos, WINDOW_HEIGHT - ypos);
		if (flock.boids.size() > 0)
		{
			bool done = false;
			for (int i = 0; i < flock.boids.size(); i++)
			{
				if (flock.boids[i].pos.distance(cursorPos) < 15.0f)
				{
					flock.boids.erase(flock.boids.begin() + i);
					done = true;
					break;
				}
			}
			if (!done)
			{
				Boid b(xpos, WINDOW_HEIGHT - ypos);
				flock.addBoid(b);
			}
		}
		else
		{
			Boid b(xpos, WINDOW_HEIGHT - ypos);
			flock.addBoid(b);
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Vector2 cursorPos(xpos, WINDOW_HEIGHT - ypos);
		if (isAttractor)
		{			
			if (flock.attractor.size() > 0)
			{
				bool done = false;
				for (int i = 0; i < flock.attractor.size(); i++)
				{
					if (flock.attractor[i].pos.distance(cursorPos) < 12.0f)
					{
						flock.attractor.erase(flock.attractor.begin() + i);
						done = true;
						break;
					}
				}

				if (!done)
				{
					Attractor a(xpos, WINDOW_HEIGHT - ypos);
					flock.addAttractor(a);
				}
			}
			else
			{
				Attractor a(xpos, WINDOW_HEIGHT - ypos);
				flock.addAttractor(a);
			}
		}
		else
		{
			if (flock.repeller.size() > 0)
			{
				bool done = false;
				for (int i = 0; i < flock.repeller.size(); i++)
				{
					if (flock.repeller[i].pos.distance(cursorPos) < 12.0f)
					{
						flock.repeller.erase(flock.repeller.begin() + i);
						done = true;
						break;
					}
				}

				if (!done)
				{
					Repeller r(xpos, WINDOW_HEIGHT - ypos);
					flock.addRepeller(r);
				}
			}
			else
			{
				Repeller r(xpos, WINDOW_HEIGHT - ypos);
				flock.addRepeller(r);
			}
		}		
	}
}
#endif