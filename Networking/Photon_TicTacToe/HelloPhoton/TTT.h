#pragma once
#include "windows.h"
#include "Vector.h"
#include "GLFW/glfw3.h"
#include <GL/GLU.h>
#include <iostream>
#include "Bitmap.h"

class TicTacToe
{
public:
	float grid[9];
	float winner;
	GLuint mTextureID[7];

	TicTacToe();	
	void Init();
	void DrawGridBackground();
	void DrawGrid();
	void DrawXO(int row, int col, float player);
	void loadTexture(const char* path, GLuint textureID);
	void reset();
	void setGrid(int row, int col, float value);
	bool isEmpty(int row, int col);
	void CheckCondition();	
	void DrawUI(float offsetX, float offsetY, float sizeX, float sizeY, bool isFirst, bool canMove);
	void draw(bool isFirst, bool canMove);
};
