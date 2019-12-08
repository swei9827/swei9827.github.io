#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <GLFW/glfw3.h>
#include "demo_base.h"
#include "GameOfLife.h"

#include <GL/GLU.h>

using namespace std;

int main(int argc, char *argv[]);
int i4_max(int i1, int i2);
int i4_min(int i1, int i2);
int i4_modp(int i, int j);
int i4_uniform(int a, int b, int *seed);
void my_init();
float r4_abs(float x);
int r4_nint(float x);

void MouseCallback(GLFWwindow* window, int button, int action, int mods);
//
//  Global data.
//
int box_size;
int seed = 123456789;
bool *state;
int m;
int n;
bool isPlay;
bool board1;
int pixel_height;
int pixel_width;
GLFWwindow* window;
GameOfLife* gameoflife = new GameOfLife();

//****************************************************************************80
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

// Simple camera controller. (MOUSE)
///Camera gCamera;
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

	///gCamera.rotate(offsetX * 0.1f, Vector(0.0f, 1.0f, 0.0f));
	///gCamera.rotateLocal(offsetY * 0.1f, Vector(1.0f, 0.0f, 0.0f));
}

int main(int argc, char *argv[])
{

	int i;
	int j;

	cout << "\n";
	cout << "LIFE_OPENGL\n";
	cout << "  C++ version\n";
	cout << "\n";
	cout << "  Compiled on " << __DATE__ << " at " << __TIME__ << ".\n";

	state = new bool[m * n];
	for (j = 0; j < n; j++)
	{
		for (i = 0; i < m; i++)
		{
			state[i + j * m] = false;
		}
	}

	int running = GL_TRUE;

	//GLFWwindow* window;

	/* Initialize the GLFW library */
	if (!glfwInit())
		return -1;

	// Open an OpenGL window
	window = glfwCreateWindow(640, 410, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Hook window resize.
	glfwSetWindowSizeCallback(window, onWindowResized);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	onWindowResized(window, 640, 410);

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


														//glutInitWindowSize(pixel_width, pixel_height);
														//glutInitWindowPosition(0, 0);

														///glutCreateWindow("Life");
														///glutDisplayFunc(display);
	my_init();
	gameoflife->init();
	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// OpenGL rendering goes here...
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//display();
		glfwSetMouseButtonCallback(window, MouseCallback);		

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			cout << "x:" << xpos << endl << "y:" << ypos << endl;
			if (xpos >= 20 && xpos <= 620 && ypos >= 10 && ypos <= 360)
			{
				i = (xpos - 20) / gameoflife->box_size;
				j = (ypos - 10) / gameoflife->box_size;
				gameoflife->Select(gameoflife->m, gameoflife->n, gameoflife->state, j, i);
			}
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			if (xpos >= 20 && xpos <= 620 && ypos >= 10 && ypos <= 360)
			{
				i = (xpos - 20) / gameoflife->box_size;
				j = (ypos - 10) / gameoflife->box_size;
				gameoflife->Deselect(gameoflife->m, gameoflife->n, gameoflife->state, j, i);
			}			
		}

		// Check if ESC key was pressed
		if (glfwGetKey(window, GLFW_KEY_ESCAPE))
			break;

		gameoflife->draw();

		// Swap front and back rendering buffers
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	gameoflife->deinit();
	delete gameoflife;

	// Close window and terminate GLFW
	glfwTerminate();
	//delete[] state;
	return 0;
}

int i4_max(int i1, int i2)
{
	int value;

	if (i2 < i1)
	{
		value = i1;
	}
	else
	{
		value = i2;
	}
	return value;
}

int i4_min(int i1, int i2)
{
	int value;

	if (i1 < i2)
	{
		value = i1;
	}
	else
	{
		value = i2;
	}
	return value;
}
//****************************************************************************80

int i4_modp(int i, int j)
{
	int value;

	if (j == 0)
	{
		cerr << "\n";
		cerr << "I4_MODP - Fatal error!\n";
		cerr << "  I4_MODP ( I, J ) called with J = " << j << "\n";
		exit(1);
	}

	value = i % j;

	if (value < 0)
	{
		value = value + abs(j);
	}

	return value;
}


int i4_uniform(int a, int b, int *seed)
{
	int k;
	float r;
	int value;

	if (*seed == 0)
	{
		cerr << "\n";
		cerr << "I4_UNIFORM - Fatal error!\n";
		cerr << "  Input value of SEED = 0.\n";
		exit(1);
	}

	k = *seed / 127773;

	*seed = 16807 * (*seed - k * 127773) - k * 2836;

	if (*seed < 0)
	{
		*seed = *seed + 2147483647;
	}

	r = (float)(*seed) * 4.656612875E-10;
	//
	//  Scale R to lie between A-0.5 and B+0.5.
	//
	r = (1.0 - r) * ((float)(i4_min(a, b)) - 0.5)
		+ r * ((float)(i4_max(a, b)) + 0.5);
	//
	//  Use rounding to convert R to an integer between A and B.
	//
	value = r4_nint(r);

	value = i4_max(value, i4_min(a, b));
	value = i4_min(value, i4_max(a, b));

	return value;
}

void my_init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//
	//  Change this to proportions for MxN
	//
	gluOrtho2D(-20.0, (double)620, -50.0, (double)360.0);
	glMatrixMode(GL_MODELVIEW);

	return;
}


float r4_abs(float x)
{
	float value;

	if (0.0 <= x)
	{
		value = x;
	}
	else
	{
		value = -x;
	}
	return value;
}

int r4_nint(float x)
{
	int value;

	if (x < 0.0)
	{
		value = -(int)(r4_abs(x) + 0.5);
	}
	else
	{
		value = (int)(r4_abs(x) + 0.5);
	}

	return value;
}

void MouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		if (ypos >= 370 && ypos <= 400 && xpos >= 30 && xpos <= 70)
		{
			gameoflife->isPlay = !gameoflife->isPlay;
		}
		else if (ypos >= 370 && ypos <= 400 && xpos >= 80 && xpos <= 120)
		{
			gameoflife->Clear();
		}
		else if (ypos >= 370 && ypos <= 400 && xpos >= 130 && xpos <= 170)
		{
			if (gameoflife->board1)
			{
				gameoflife->m = 70;
				gameoflife->n = 120;
				gameoflife->box_size = 5;
			}
			else
			{
				gameoflife->m = 35;
				gameoflife->n = 60;
				gameoflife->box_size = 10;
			}
			gameoflife->state = new bool[gameoflife->m * gameoflife->n];
			for (int j = 0; j < gameoflife->n; j++)
			{
				for (int i = 0; i < gameoflife->m; i++)
				{
					gameoflife->state[i + j * gameoflife->m] = false;
				}
			}
			gameoflife->board1 = !gameoflife->board1;
		}
		else if (ypos >= 370 && ypos <= 400 && xpos >= 180 && xpos <= 220)
		{
			
		}
	}
}