#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(const std::string& file)
{
	glGenTextures(1, &GtextureID);
	loadTexture(file.c_str(), GtextureID);
}

Sprite::~Sprite()
{

}

void Sprite::draw(float x, float y, float rotation, float scale, const Color& color)
{
	Matrix translate = Matrix::makeTranslationMatrix(x, y, 0.0f);
	Matrix translate2 = Matrix::makeTranslationMatrix(-x, -y, 0.0f);
	Matrix rotate = Matrix::makeRotateMatrix(rotation, Vector(0, 0, 1.0f));
	Matrix Scale = Matrix::makeScaleMatrix(scale, scale, 1.0f);
	Matrix viewSpaceMatrix = translate* rotate * Scale* translate2 ;

	glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, GtextureID);

	glBegin(GL_TRIANGLES);
	glColor3f(color.r, color.g, color.b);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x - m_width / 2, y - m_height / 2);

	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x + m_width / 2, y - m_height / 2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x + m_width / 2, y + m_height / 2);

	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x + m_width / 2, y + m_height / 2);

	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(x - m_width / 2, y + m_height / 2);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x - m_width / 2, y - m_height / 2);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Sprite::loadTexture(const char* path, GLuint textureID)
{
	CBitmap bitmap(path);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// bilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());

	m_height = bitmap.GetHeight();
	m_width = bitmap.GetWidth();
	std::cout << "Texture Loaded" << std::endl;
}