// 0118888_GameEngine.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "GLFW/glfw3.h"
#include "GL/glu.h"
#include "Application.h"

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void onWindowResized(GLFWwindow* window, int width, int height)
{
	if (height == 0) height = 1;						// Prevent A Divide By Zero By making Height Equal One

	glViewport(0, 0, width, height);					// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}


void gameUpdate(float fps, float deltaTime)
{
	std::cout << "Fps: " << fps << " delta time : " << deltaTime << std::endl;
}

int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
		return -1;

	window = glfwCreateWindow(WINDOW_WIDTH,WINDOW_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);

	glfwMakeContextCurrent(window);


	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	//glfwSwapInterval(0); //enable/disable vsync

	Application app(glfwGetTime());
	app.start();
	//limit fps
	float targetFps = 30;
	float minDeltaTime = 1.0 / targetFps;


	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//delta time
		app.update(glfwGetTime());
		app.draw();

		//show results
		//gameUpdate(app.fps, app.deltaTime);

		//===============================
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}