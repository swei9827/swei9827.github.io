#include "TTT.h"

TicTacToe::TicTacToe()
{
	for (int i = 0; i < 9; i++)
	{
		grid[i] = -1;
	}
	winner = -1;
}

void TicTacToe::Init()
{
	glGenTextures(7, mTextureID);
	loadTexture("../media/GridBackground.bmp", mTextureID[0]);
	loadTexture("../media/Cross.bmp", mTextureID[1]);
	loadTexture("../media/Circle.bmp", mTextureID[2]);
	loadTexture("../media/Reset.bmp", mTextureID[3]);
	loadTexture("../media/YouAre.bmp", mTextureID[4]);
	loadTexture("../media/Turn.bmp", mTextureID[5]);
	loadTexture("../media/Winner.bmp", mTextureID[6]);
	std::cout << mTextureID[4] << mTextureID[5] << std::endl;
	for (int i = 0; i < 9; i++)
	{
		grid[i] = -1;
	}
	winner = -1;
}

void TicTacToe::DrawGridBackground()
{
	float size = 300.0f;
	float offsetX = 400.0f;
	float offsetY = 100.0f;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureID[0]);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX, offsetY, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(offsetX + size, offsetY, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + size, offsetY + size, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + size, offsetY + size, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(offsetX, offsetY + size, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX, offsetY, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void TicTacToe::DrawGrid()
{
	for (int i = 0; i < 9; i++)
	{
		if (grid[i] != -1)
			DrawXO(i / 3, i % 3, grid[i]);
	}
}

void TicTacToe::DrawXO(int row, int col, float player)
{
	float offsetX = 400.0f;
	float offsetY = 100.0f;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureID[int(player)]);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX + col * 100.0f, offsetY + (2 - row) * 100.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(offsetX + (col + 1) *100.0f, offsetY + (2 - row) * 100.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + (col + 1) *100.0f, offsetY + ((2 - row) + 1) * 100.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + (col + 1) *100.0f, offsetY + ((2 - row) + 1) * 100.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(offsetX + col * 100.0f, offsetY + ((2 - row) + 1) * 100.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX + col * 100.0f, offsetY + (2 - row) * 100.0f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void TicTacToe::loadTexture(const char* path, GLuint textureID)
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

void TicTacToe::reset()
{
	for (int i = 0; i < 9; i++)
	{
		grid[i] = -1;
	}
	winner = -1;
}

void TicTacToe::setGrid(int row, int col, float value)
{
	grid[(row * 3) + (col)] = value;
}

bool TicTacToe::isEmpty(int row, int col)
{
	if (grid[(row * 3) + (col)] == -1)
	{
		std::cout << "empty" << std::endl;
		return true;
	}
	else
	{
		std::cout << "Not empty" << std::endl;
		return false;
	}
}

void TicTacToe::CheckCondition()
{
	winner = -1;
	//check horizontal
	if (grid[0] == grid[1] && grid[0] == grid[2])
	{
		winner = grid[0];
	}
	else if (grid[3] == grid[4] && grid[3] == grid[5])
	{
		winner = grid[3];
	}
	else if (grid[6] == grid[7] && grid[6] == grid[8])
	{
		winner = grid[6];
	}
	//vertical
	else if (grid[0] == grid[3] && grid[0] == grid[6])
	{
		winner = grid[0];
	}
	else if (grid[1] == grid[4] && grid[1] == grid[7])
	{
		winner = grid[1];
	}
	else if (grid[2] == grid[5] && grid[2] == grid[8])
	{
		winner = grid[2];
	}
	//diagonal
	else if (grid[0] == grid[4] && grid[0] == grid[8])
	{
		winner = grid[0];
	}
	else if (grid[2] == grid[4] && grid[2] == grid[6])
	{
		winner = grid[2];
	}
}

void TicTacToe::DrawUI(float offsetX, float offsetY, float sizeX, float sizeY, bool isFirst, bool canMove)
{
	// reset button
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureID[3]);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX, offsetY, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(offsetX + sizeX, offsetY, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + sizeX, offsetY + sizeY, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + sizeX, offsetY + sizeY, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(offsetX, offsetY + sizeY, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX, offsetY, 0.0f);
	glEnd();

	// player type
	glBindTexture(GL_TEXTURE_2D, mTextureID[4]);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX, offsetY - 100.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(offsetX + sizeX, offsetY - 100.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + sizeX, offsetY + sizeY - 100.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + sizeX, offsetY + sizeY - 100.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(offsetX, offsetY + sizeY - 100.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX, offsetY - 100.0f, 0.0f);
	glEnd();

	if (isFirst)
		glBindTexture(GL_TEXTURE_2D, mTextureID[1]); // cross
	else
		glBindTexture(GL_TEXTURE_2D, mTextureID[2]); // circle

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX + 100.0f, offsetY - 100.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(offsetX + 50.0f + 100.0f, offsetY - 100.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + 50.0f + 100.0f, offsetY + sizeY - 100.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + 50.0f + 100.0f, offsetY + sizeY - 100.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(offsetX + 100.0f, offsetY + sizeY - 100.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX + 100.0f, offsetY - 100.0f, 0.0f);
	glEnd();

	// Turn
	glBindTexture(GL_TEXTURE_2D, mTextureID[5]);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX, offsetY - 200.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(offsetX + sizeX, offsetY - 200.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + sizeX, offsetY + sizeY - 200.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + sizeX, offsetY + sizeY - 200.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(offsetX, offsetY + sizeY - 200.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX, offsetY - 200.0f, 0.0f);
	glEnd();

	if (isFirst)
		if (canMove)
			glBindTexture(GL_TEXTURE_2D, mTextureID[1]); // cross
		else
			glBindTexture(GL_TEXTURE_2D, mTextureID[2]); // circle
	else
		if (canMove)
			glBindTexture(GL_TEXTURE_2D, mTextureID[2]); // circle
		else
			glBindTexture(GL_TEXTURE_2D, mTextureID[1]); // cross

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX + 100.0f, offsetY - 200.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(offsetX + 50.0f + 100.0f, offsetY - 200.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + 50.0f + 100.0f, offsetY + sizeY - 200.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + 50.0f + 100.0f, offsetY + sizeY - 200.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(offsetX + 100.0f, offsetY + sizeY - 200.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX + 100.0f, offsetY - 200.0f, 0.0f);
	glEnd();

	//winner
	glBindTexture(GL_TEXTURE_2D, mTextureID[6]);

	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX, offsetY - 300.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(offsetX + sizeX, offsetY - 300.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + sizeX, offsetY + sizeY - 300.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + sizeX, offsetY + sizeY - 300.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(offsetX, offsetY + sizeY - 300.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX, offsetY - 300.0f, 0.0f);
	glEnd();

	if (winner != -1)
	{
		if (winner == 1)
		{
			glBindTexture(GL_TEXTURE_2D, mTextureID[1]);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, mTextureID[2]);
		}
		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX + 100.0f, offsetY - 300.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(offsetX + 50.0f + 100.0f, offsetY - 300.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + 50.0f + 100.0f, offsetY + sizeY - 300.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(offsetX + 50.0f + 100.0f, offsetY + sizeY - 300.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(offsetX + 100.0f, offsetY + sizeY - 300.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(offsetX + 100.0f, offsetY - 300.0f, 0.0f);
		glEnd();
	}

	glDisable(GL_TRIANGLES);
}


void TicTacToe::draw(bool isFirst, bool canMove)
{
	DrawGridBackground();
	DrawGrid();
	DrawUI(100, 500, 80, 50, isFirst, canMove);
}

