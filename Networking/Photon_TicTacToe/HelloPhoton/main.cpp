#include "MyPhoton.h"
#include "TTT.h"

using namespace std;

const int RESOLUTION_X = 800;
const int RESOLUTION_Y = 600;

TicTacToe ttt;
float mouseX;
float mouseY;
float offsetX = 400.0f;
float offsetY = 100.0f;

void onWindowResized(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//! Use ortho2D view
	gluOrtho2D(0, width, 0, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		//MyPhoton::getInstance().sendMyData();
		//MyPhoton::getInstance().sendMyData(mouseX, mouseY);
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouseX = xpos;
	mouseY = RESOLUTION_Y - ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		int player = 0;
		if (MyPhoton::getInstance().isFirst)
		{
			player = 1;
		}
		else
		{
			player = 2;
		}

		if (mouseX >= (100.0f) && mouseX < (180.0f) && mouseY >= (500.0f) && mouseY < (550.0f))
		{
			ttt.reset();
			MyPhoton::getInstance().sendMyData(ttt.grid);
		}

		if (MyPhoton::getInstance().canMove && ttt.winner < 0)
		{
			if (mouseX >= (offsetX) && mouseX < (offsetX + 100.f) && mouseY >= (offsetY) && mouseY < (offsetY + 100.0f) && ttt.isEmpty(2, 0))
			{
					ttt.setGrid(2, 0, player);
					MyPhoton::getInstance().sendMyData(ttt.grid);
			}
			else if (mouseX >= (offsetX + 100.0f) && mouseX < (offsetX + 200.f) && mouseY >= (offsetY) && mouseY < (offsetY + 100.0f) && ttt.isEmpty(2, 1))
			{
					ttt.setGrid(2, 1, player);
					MyPhoton::getInstance().sendMyData(ttt.grid);
			}
			else if (mouseX >= (offsetX + 200.0f) && mouseX < (offsetX + 300.f) && mouseY >= (offsetY) && mouseY < (offsetY + 100.0f) && ttt.isEmpty(2, 2))
			{
					ttt.setGrid(2, 2, player);
					MyPhoton::getInstance().sendMyData(ttt.grid);
			}
			else if (mouseX >= (offsetX) && mouseX < (offsetX + 100.f) && mouseY >= (offsetY + 100.0f) && mouseY < (offsetY + 200.0f) && ttt.isEmpty(1, 0))
			{
					ttt.setGrid(1, 0, player);
					MyPhoton::getInstance().sendMyData(ttt.grid);
			}
			else if (mouseX >= (offsetX + 100.0f) && mouseX < (offsetX + 200.f) && mouseY >= (offsetY + 100.0f) && mouseY < (offsetY + 200.0f) && ttt.isEmpty(1, 1))
			{
					ttt.setGrid(1, 1, player);
					MyPhoton::getInstance().sendMyData(ttt.grid);
			}
			else if (mouseX >= (offsetX + 200.0f) && mouseX < (offsetX + 300.f) && mouseY >= (offsetY + 100.0f) && mouseY < (offsetY + 200.0f) && ttt.isEmpty(1, 2))
			{
					ttt.setGrid(1, 2, player);
					MyPhoton::getInstance().sendMyData(ttt.grid);
			}
			else if (mouseX >= (offsetX) && mouseX < (offsetX + 100.f) && mouseY >= (offsetY + 200.0f) && mouseY < (offsetY + 300.0f) && ttt.isEmpty(0, 0))
			{
					ttt.setGrid(0, 0, player);
					MyPhoton::getInstance().sendMyData(ttt.grid);
			}
			else if (mouseX >= (offsetX + 100.0f) && mouseX < (offsetX + 200.f) && mouseY >= (offsetY + 200.0f) && mouseY < (offsetY + 300.0f) && ttt.isEmpty(0, 1))
			{
					ttt.setGrid(0, 1, player);
					MyPhoton::getInstance().sendMyData(ttt.grid);
			}
			else if (mouseX >= (offsetX + 200.0f) && mouseX < (offsetX + 300.f) && mouseY >= (offsetY + 200.0f) && mouseY < (offsetY + 300.0f) && ttt.isEmpty(0, 2))
			{
					ttt.setGrid(0, 2, player);
					MyPhoton::getInstance().sendMyData(ttt.grid);
			}
			ttt.DrawGrid();		
		}
	}
}

int main (void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create m_a windowed mode window and its OpenGL context */
	window = glfwCreateWindow (RESOLUTION_X, RESOLUTION_Y, "", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback (window, onWindowResized);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	onWindowResized (window, RESOLUTION_X, RESOLUTION_Y);

	MyPhoton::getInstance().connect();
	ttt.Init();
	
	while (!glfwWindowShouldClose(window))
	{		
		MyPhoton::getInstance().run();
		glClear(GL_COLOR_BUFFER_BIT);
		for (int i = 0; i < 9; i++)
		{
			ttt.grid[i] = MyPhoton::getInstance().ttt.grid[i];
		}
		ttt.draw(MyPhoton::getInstance().isFirst,MyPhoton::getInstance().canMove);
		ttt.CheckCondition();
		
		
		glfwSwapBuffers (window);
		glfwPollEvents ();

		/*if (ttt.winner != -1)
		{
			cout << "Winner is player " << ttt.winner;
			system("PAUSE");
			break;
		}*/
	}

	glfwTerminate();
	return 0;
}