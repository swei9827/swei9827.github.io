#ifndef _TRIANGLE_DEMO_H
#define _TRIANGLE_DEMO_H

#include "demo_base.h"
#include "Bitmap.h"
#include <fmod.hpp>
#include <fmod_errors.h>

#define TEXTURE_COUNT 2
#define SPECTRUM_SIZE 128

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout<<"FMOD error! : " << FMOD_ErrorString(result) << std::endl;
	}
}

#define RECT_VERTICE_W 50
#define RECT_VERTICE_H 50
//every quad has 6 vertices
const int RECT_VERTEX_COUNT = (RECT_VERTICE_W )*(RECT_VERTICE_H) * 6;
// every vertex has 3 components(x,y,z)
const int RECT_VERTEX_ARRAY_SIZE = RECT_VERTEX_COUNT * 3;
const int RECT_UV_ARRAY_SIZE = RECT_VERTEX_COUNT * 2;

class AudioVisualizer : public DemoBase
{
private:
	GLuint mTextureID[TEXTURE_COUNT];
	float m_rotation;

	float mWaveRadianOffset;
	GLfloat mRectVertices[RECT_VERTEX_ARRAY_SIZE];
	GLfloat mRectUV[RECT_UV_ARRAY_SIZE];

	// Fmod
	FMOD::System* m_fmodSystem;
	FMOD::Sound* m_music;
	FMOD::Channel *m_musicChannel;
	float m_spectrumLeft[SPECTRUM_SIZE];
	float m_spectrumRight[SPECTRUM_SIZE];

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

	void initFmod()
	{
		FMOD_RESULT result;
		unsigned int version;

		result = FMOD::System_Create(&m_fmodSystem);
		ERRCHECK(result);

		result = m_fmodSystem->getVersion(&version);
		ERRCHECK(result);

		if (version < FMOD_VERSION)
			std::cout << "FMOD ERROR! You are using an old version of FMOD" << std::endl;

		//initialize fmod system
		result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, 0);
		ERRCHECK(result);

		//load and set up music
		result = m_fmodSystem->createStream("../media/La Vie en Rose.mp3", FMOD_SOFTWARE, 0, &m_music);
		ERRCHECK(result);

		//play the loaded mp3 music
		result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
		ERRCHECK(result);
	}

	void init()
	{
		m_rotation = 0;
		initFmod();

		glGenTextures(TEXTURE_COUNT, mTextureID);
		loadTexture("../media/night.bmp", mTextureID[0]);
		loadTexture("../media/glass.bmp", mTextureID[1]);

		mWaveRadianOffset = 0.0f;
	}

	void deinit()
	{

	}


	void genPlane(float offsetRadian)
	{
		const float width = 15.0f;
		const float height = 15.0f;
		const float halfWidth = width * 0.5f;
		const float halfHeight = height * 0.5f;

		const float waveAmpMul = m_spectrumLeft[0] * m_spectrumRight[0];
		const float xToRadianMul = 5.0f;

		const float texMul = 1.0f;

		int currentVert = -1;
		int currentIndex = -1;
		for (int h = 0; h<RECT_VERTICE_H - 1; h++)
		{
			for (int w = 0; w<RECT_VERTICE_W - 1; w++)
			{
				//========= 6 vertices to form one sub-rectangle

				//1st vertex
				int vertex1 = ++currentVert;
				mRectVertices[vertex1 * 3] = -halfWidth + (float)(w) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex1 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex1 * 3] * xToRadianMul);
				mRectVertices[vertex1 * 3 + 2] = -halfHeight + (float)(h) / (float)RECT_VERTICE_H * height;
				mRectUV[vertex1 * 2] = (float)(w) / (float)RECT_VERTICE_W * texMul;				///mRectuV[0] = 0	mRectUV[2] = 1/200
				mRectUV[vertex1 * 2 + 1] = (float)(h) / (float)RECT_VERTICE_H* texMul;			///mRectUV[1] = 0   mRectUV[3] = 0

				//2nd vertex
				int vertex2 = ++currentVert;
				mRectVertices[vertex2 * 3] = -halfWidth + (float)(w) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex2 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex2 * 3] * xToRadianMul);
				mRectVertices[vertex2 * 3 + 2] = -halfHeight + (float)(h + 1) / (float)RECT_VERTICE_H * height;
				mRectUV[vertex2 * 2] = (float)(w) / (float)RECT_VERTICE_W* texMul;
				mRectUV[vertex2 * 2 + 1] = (float)(h + 1) / (float)RECT_VERTICE_H* texMul;


				//3rd vertex
				int vertex3 = ++currentVert;
				mRectVertices[vertex3 * 3] = -halfWidth + (float)(w + 1) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex3 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex3 * 3] * xToRadianMul);
				mRectVertices[vertex3 * 3 + 2] = -halfHeight + (float)(h + 1) / (float)RECT_VERTICE_H * height;
				mRectUV[vertex3 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
				mRectUV[vertex3 * 2 + 1] = (float)(h + 1) / (float)RECT_VERTICE_H * texMul;


				//4th vertex
				int vertex4 = ++currentVert;
				mRectVertices[vertex4 * 3] = mRectVertices[vertex3 * 3];
				mRectVertices[vertex4 * 3 + 1] = mRectVertices[vertex3 * 3 + 1];
				mRectVertices[vertex4 * 3 + 2] = mRectVertices[vertex3 * 3 + 2];
				mRectUV[vertex4 * 2] = mRectUV[vertex3 * 2];
				mRectUV[vertex4 * 2 + 1] = mRectUV[vertex3 * 2 + 1];


				//5th vertex
				int vertex5 = ++currentVert;
				mRectVertices[vertex5 * 3] = -halfWidth + (float)(w + 1) / (float)RECT_VERTICE_W * width;
				mRectVertices[vertex5 * 3 + 1] = waveAmpMul * cos(offsetRadian + mRectVertices[vertex5 * 3] * xToRadianMul);
				mRectVertices[vertex5 * 3 + 2] = -halfHeight + (float)(h) / (float)RECT_VERTICE_H * height;
				mRectUV[vertex5 * 2] = (float)(w + 1) / (float)RECT_VERTICE_W * texMul;
				mRectUV[vertex5 * 2 + 1] = (float)(h) / (float)RECT_VERTICE_H * texMul;

				//6th vertex
				int vertex6 = ++currentVert;
				mRectVertices[vertex6 * 3] = mRectVertices[vertex1 * 3];
				mRectVertices[vertex6 * 3 + 1] = mRectVertices[vertex1 * 3 + 1];
				mRectVertices[vertex6 * 3 + 2] = mRectVertices[vertex1 * 3 + 2];
				mRectUV[vertex6 * 2] = mRectUV[vertex1 * 2];
				mRectUV[vertex6 * 2 + 1] = mRectUV[vertex1 * 2 + 1];
			}
		}
	}
	void drawWorldOriginLines(const Matrix& viewMatrix)
	{
		// draw axis.
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
	}

	void drawWave()
	{
		m_fmodSystem->update();

		//GEt spectrum for left and right stereo channels
		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		mWaveRadianOffset += m_spectrumLeft[1];
		if (mWaveRadianOffset > 2.0f * M_PI)
			mWaveRadianOffset -= 2.0f * M_PI;
		genPlane(mWaveRadianOffset);

		glColor3f(1.0f, 1.0f, 1.0f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, mRectVertices);
		glTexCoordPointer(2, GL_FLOAT, 0, mRectUV);

		glDrawArrays(GL_TRIANGLES, 0, RECT_VERTEX_COUNT);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void drawRectLeftSpec(float x,float y,float z,int i,float mul)
	{
		m_fmodSystem->update();

		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		float xStart = x;
		float yStart = y;
		float zStart = z;

		float width = 0.5f;
		float height = 0.5f;
		float depth = 0.5f;

		float xOffset = xStart - width / 2;
		float yOffset = yStart - height / 2;
		float zOffset = zStart - depth / 2;		

		float spectrumAmpMul = m_spectrumLeft[i] * mul;// * m_spectrumRight[0];
		
		GLfloat cube[] =
		{
			//1st face / back
			xOffset,yStart,zOffset,
			xOffset+width,yStart,zOffset,
			xOffset+width,spectrumAmpMul,zOffset,
			xOffset+width,spectrumAmpMul,zOffset,
			xOffset,spectrumAmpMul,zOffset,
			xOffset,yStart,zOffset,

			//2nd face / front
			xOffset,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset + depth,
			xOffset,spectrumAmpMul,zOffset + depth,
			xOffset,yStart,zOffset + depth,

			//3rd face / left
			xOffset,yStart,zOffset,
			xOffset,yStart,zOffset + depth,
			xOffset,spectrumAmpMul,zOffset + depth,
			xOffset,spectrumAmpMul,zOffset + depth,
			xOffset,spectrumAmpMul,zOffset,
			xOffset,yStart,zOffset,

			//4th face / right
			xOffset + width,yStart,zOffset,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset,
			xOffset + width,yStart,zOffset,

			//5th face / top
			xOffset,spectrumAmpMul,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset,
			xOffset + width,spectrumAmpMul,zOffset,
			xOffset,spectrumAmpMul,zOffset,
			xOffset,spectrumAmpMul,zOffset + depth,

			//6th face / bottom
			xOffset,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset,
			xOffset + width,yStart,zOffset,
			xOffset,yStart,zOffset,
			xOffset,yStart,zOffset + depth
		};

		GLubyte colors[] =
		{
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,

			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,

			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,

			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,

			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,

			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
			255 - m_spectrumLeft[i] * 255,128,255,
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0,cube);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void drawRectLeftSpec2(float x, float y, float z, int i, float mul)
	{
		m_fmodSystem->update();

		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		float xStart = x;
		float yStart = y;
		float zStart = z;

		float width = 0.5f;
		float height = 0.5f;
		float depth = 0.5f;

		float xOffset = xStart - width / 2;
		float yOffset = yStart - height / 2;
		float zOffset = zStart - depth / 2;

		float spectrumAmpMul = m_spectrumLeft[i] * mul;// * m_spectrumRight[0];

		GLfloat cube[] =
		{
			//1st face / back
			xOffset,yStart,zOffset,
			xOffset + width,yStart,zOffset,
			xOffset + width,spectrumAmpMul,zOffset,
			xOffset + width,spectrumAmpMul,zOffset,
			xOffset,spectrumAmpMul,zOffset,
			xOffset,yStart,zOffset,

			//2nd face / front
			xOffset,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset + depth,
			xOffset,spectrumAmpMul,zOffset + depth,
			xOffset,yStart,zOffset + depth,

			//3rd face / left
			xOffset,yStart,zOffset,
			xOffset,yStart,zOffset + depth,
			xOffset,spectrumAmpMul,zOffset + depth,
			xOffset,spectrumAmpMul,zOffset + depth,
			xOffset,spectrumAmpMul,zOffset,
			xOffset,yStart,zOffset,

			//4th face / right
			xOffset + width,yStart,zOffset,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset,
			xOffset + width,yStart,zOffset,

			//5th face / top
			xOffset,spectrumAmpMul,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset + depth,
			xOffset + width,spectrumAmpMul,zOffset,
			xOffset + width,spectrumAmpMul,zOffset,
			xOffset,spectrumAmpMul,zOffset,
			xOffset,spectrumAmpMul,zOffset + depth,

			//6th face / bottom
			xOffset,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset,
			xOffset + width,yStart,zOffset,
			xOffset,yStart,zOffset,
			xOffset,yStart,zOffset + depth
		};

		GLubyte colors[] =
		{
			255,255,255,
			255,255,255,
			255,0,65,
			255,0,65,
			255,0,65,
			255,255,255,

			255,255,255,
			255,255,255,
			255,0,65,
			255,0,65,
			255,0,65,
			255,255,255,

			255,255,255,
			255,255,255,
			255,0,65,
			255,0,65,
			255,0,65,
			255,255,255,

			255,255,255,
			255,255,255,
			255,0,65,
			255,0,65,
			255,0,65,
			255,255,255,

			255,0,65,
			255,0,65,
			255,0,65,
			255,0,65,
			255,0,65,

			255,255,255,
			255,255,255,
			255,255,255,
			255,255,255,
			255,255,255,
			255,255,255,
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, cube);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void drawRectRightSpec(float x, float y, float z, int i,float mul)
	{
		m_fmodSystem->update();

		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		float xStart = x;
		float yStart = y;
		float zStart = z;

		float width = 0.5f;
		float height = 0.5f;
		float depth = 0.5f;

		float xOffset = xStart - width / 2;
		float yOffset = yStart - height / 2;
		float zOffset = zStart - depth / 2;

		float spectrumAmpMul = m_spectrumLeft[16-i] * mul;// * m_spectrumRight[0];

		GLfloat cube[] =
		{
			//1st face / back
			xOffset,yStart,zOffset,
			xOffset + width,yStart,zOffset,
			xOffset + width,-spectrumAmpMul,zOffset,
			xOffset + width,-spectrumAmpMul,zOffset,
			xOffset,-spectrumAmpMul,zOffset,
			xOffset,yStart,zOffset,

			//2nd face / front
			xOffset,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset + depth,
			xOffset,-spectrumAmpMul,zOffset + depth,
			xOffset,yStart,zOffset + depth,

			//3rd face / left
			xOffset,yStart,zOffset,
			xOffset,yStart,zOffset + depth,
			xOffset,-spectrumAmpMul,zOffset + depth,
			xOffset,-spectrumAmpMul,zOffset + depth,
			xOffset,-spectrumAmpMul,zOffset,
			xOffset,yStart,zOffset,

			//4th face / right
			xOffset + width,yStart,zOffset,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset,
			xOffset + width,yStart,zOffset,

			//5th face / bottom
			xOffset,-spectrumAmpMul,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset,
			xOffset + width,-spectrumAmpMul,zOffset,
			xOffset,-spectrumAmpMul,zOffset,
			xOffset,-spectrumAmpMul,zOffset + depth,

			//6th face / top
			xOffset,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset,
			xOffset + width,yStart,zOffset,
			xOffset,yStart,zOffset,
			xOffset,yStart,zOffset + depth
		};

		GLubyte colors[] =
		{
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,

			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,

			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,

			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,

			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,

			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
			255,128,255 - m_spectrumRight[16 - i] * 255,
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, cube);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void drawRectRightSpec2(float x, float y, float z, int i, float mul)
	{
		m_fmodSystem->update();

		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		float xStart = x;
		float yStart = y;
		float zStart = z;

		float width = 0.5f;
		float height = 0.5f;
		float depth = 0.5f;

		float xOffset = xStart - width / 2;
		float yOffset = yStart - height / 2;
		float zOffset = zStart - depth / 2;

		float spectrumAmpMul = m_spectrumLeft[16 - i] * mul;// * m_spectrumRight[0];

		GLfloat cube[] =
		{
			//1st face / back
			xOffset,yStart,zOffset,
			xOffset + width,yStart,zOffset,
			xOffset + width,-spectrumAmpMul,zOffset,
			xOffset + width,-spectrumAmpMul,zOffset,
			xOffset,-spectrumAmpMul,zOffset,
			xOffset,yStart,zOffset,

			//2nd face / front
			xOffset,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset + depth,
			xOffset,-spectrumAmpMul,zOffset + depth,
			xOffset,yStart,zOffset + depth,

			//3rd face / left
			xOffset,yStart,zOffset,
			xOffset,yStart,zOffset + depth,
			xOffset,-spectrumAmpMul,zOffset + depth,
			xOffset,-spectrumAmpMul,zOffset + depth,
			xOffset,-spectrumAmpMul,zOffset,
			xOffset,yStart,zOffset,

			//4th face / right
			xOffset + width,yStart,zOffset,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset,
			xOffset + width,yStart,zOffset,

			//5th face / bottom
			xOffset,-spectrumAmpMul,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset + depth,
			xOffset + width,-spectrumAmpMul,zOffset,
			xOffset + width,-spectrumAmpMul,zOffset,
			xOffset,-spectrumAmpMul,zOffset,
			xOffset,-spectrumAmpMul,zOffset + depth,

			//6th face / top
			xOffset,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset + depth,
			xOffset + width,yStart,zOffset,
			xOffset + width,yStart,zOffset,
			xOffset,yStart,zOffset,
			xOffset,yStart,zOffset + depth
		};

		GLubyte colors[] =
		{
			255,255,255,
			255,255,255,
			255,175,0,
			255,175,0,
			255,175,0,
			255,255,255,

			255,255,255,
			255,255,255,
			255,175,0,
			255,175,0,
			255,175,0,
			255,255,255,

			255,255,255,
			255,255,255,
			255,175,0,
			255,175,0,
			255,175,0,
			255,255,255,

			255,255,255,
			255,255,255,
			255,175,0,
			255,175,0,
			255,175,0,
			255,255,255,

			255,175,0,
			255,175,0,
			255,175,0,
			255,175,0,
			255,175,0,

			255,255,255,
			255,255,255,
			255,255,255,
			255,255,255,
			255,255,255,
			255,255,255,
		};

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, cube);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void drawOutsideSphere(float radius, float startX, float startY, float startZ)
	{
		m_fmodSystem->update();

		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		float px, py, pz;
		const int divO = 15;
		const int divA = 15;
		const int SPHERE_ARRAY_SIZE = divO * divA * 3 * 6;
		GLfloat sphere[SPHERE_ARRAY_SIZE];
		GLfloat sphereUV[SPHERE_ARRAY_SIZE / 3 * 2];

		int currentVert = -1;

		for (int i = 0; i < divO; i++)
		{
			float tempFloat = i * 0.005f;
			if (i >= divO / 2)
			{
				tempFloat = (divO - i)* 0.005f;
			}

			for (int j = 0; j < divA; j++)
			{
				float theta = float(i) / divO * 2.0* M_PI;
				float nextTheta = (float(i) + 1) / divO * 2.0 * M_PI;

				float tempta = float(j) / divA * M_PI;
				float tempnextta = (float(j) + 1) / divA * M_PI;

				//glColor3f(0.33f - tempFloat, 0.57f - tempFloat, 0.75f - tempFloat);
				pz = cos(tempta)*radius;
				py = sin(tempta)*sin(theta)*radius;
				px = sin(tempta)*cos(theta)*radius;

				int vertex1 = ++currentVert;
				sphere[vertex1 * 3] = px + startX;
				sphere[vertex1 * 3 + 1] = py + startY;
				sphere[vertex1 * 3 + 2] = pz + startZ;
				sphereUV[vertex1 * 2] = 1;
				sphereUV[vertex1 * 2 + 1] = 0;

				pz = cos(tempta)*radius;
				py = sin(tempta)*sin(nextTheta)*radius;
				px = sin(tempta)*cos(nextTheta)*radius;

				int vertex2 = ++currentVert;
				sphere[vertex2 * 3] = px + startX;
				sphere[vertex2 * 3 + 1] = py + startY;
				sphere[vertex2 * 3 + 2] = pz + startZ;
				sphereUV[vertex2 * 2] = 0;
				sphereUV[vertex2 * 2 + 1] = 0;

				pz = cos(tempnextta)*radius;
				py = sin(tempnextta)*sin(theta)*radius;
				px = sin(tempnextta)*cos(theta)*radius;

				int vertex3 = ++currentVert;
				sphere[vertex3 * 3] = px + startX;
				sphere[vertex3 * 3 + 1] = py + startY;
				sphere[vertex3 * 3 + 2] = pz + startZ;
				sphereUV[vertex3 * 2] = 1;
				sphereUV[vertex3 * 2 + 1] = 1;
				
				pz = cos(tempnextta)*radius;
				py = sin(tempnextta)*sin(theta)*radius;
				px = sin(tempnextta)*cos(theta)*radius;

				int vertex4 = ++currentVert;
				sphere[vertex4 * 3] = px + startX;
				sphere[vertex4 * 3 + 1] = py + startY;
				sphere[vertex4 * 3 + 2] = pz + startZ;
				sphereUV[vertex4 * 2] = 1;
				sphereUV[vertex4 * 2 + 1] = 1;

				pz = cos(tempta)*radius;
				py = sin(tempta)*sin(nextTheta)*radius;
				px = sin(tempta)*cos(nextTheta)*radius;

				int vertex5 = ++currentVert;
				sphere[vertex5 * 3] = px + startX;
				sphere[vertex5 * 3 + 1] = py + startY;
				sphere[vertex5 * 3 + 2] = pz + startZ;
				sphereUV[vertex5 * 2] = 0;
				sphereUV[vertex5 * 2 + 1] = 0;

				pz = cos(tempnextta)*radius;
				py = sin(tempnextta)*sin(nextTheta)*radius;
				px = sin(tempnextta)*cos(nextTheta)*radius;

				int vertex6 = ++currentVert;
				sphere[vertex6 * 3] = px + startX;
				sphere[vertex6 * 3 + 1] = py + startY;
				sphere[vertex6 * 3 + 2] = pz + startZ;
				sphereUV[vertex6 * 2] = 0;
				sphereUV[vertex6 * 2 + 1] = 1;
			}
		}

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, mTextureID[0]);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		
		glVertexPointer(3, GL_FLOAT, 0, sphere);
		glTexCoordPointer(2, GL_FLOAT, 0, sphereUV);
		
		glDrawArrays(GL_TRIANGLES, 0, SPHERE_ARRAY_SIZE / 3);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

	}

	void drawSphere(float radius, float startX, float startY, float startZ)
	{
		m_fmodSystem->update();

		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);

		float px, py, pz;
		const int divO = 30;
		const int divA = 30;
		const int SPHERE_ARRAY_SIZE = divO*divA *3*6;
		GLfloat sphere[SPHERE_ARRAY_SIZE];

		GLubyte sphereColor[SPHERE_ARRAY_SIZE];

		int currentVert = -1;
		
		for (int i = 0; i < divO; i++)
		{
			float tempFloat = i * 0.005f;
			if (i >= divO / 2)
			{
				tempFloat = (divO - i)* 0.005f;
			}

			for (int j = 0; j < divA; j++)
			{
				float theta = float(i) / divO * 2.0* M_PI;
				float nextTheta = (float(i) + 1) / divO * 2.0 * M_PI;

				float tempta = float(j) / divA * M_PI;
				float tempnextta = (float(j) + 1) / divA * M_PI;

				//glColor3f(0.33f - tempFloat, 0.57f - tempFloat, 0.75f - tempFloat);
				pz = cos(tempta)*radius;
				py = sin(tempta)*sin(theta)*radius;
				px = sin(tempta)*cos(theta)*radius;
				
				int vertex1 = ++currentVert;
				sphere[vertex1 * 3] = px + startX;
				sphere[vertex1 * 3 + 1] = py + startY;
				sphere[vertex1 * 3 + 2] = pz + startZ;
				sphereColor[vertex1 * 3] = 255;
				sphereColor[vertex1 * 3 + 1] = 160;
				sphereColor[vertex1 * 3 + 2] = 166;

				pz = cos(tempta)*radius;
				py = sin(tempta)*sin(nextTheta)*radius;
				px = sin(tempta)*cos(nextTheta)*radius;

				int vertex2 = ++currentVert;
				sphere[vertex2 * 3] = px + startX;
				sphere[vertex2 * 3 + 1] = py + startY;
				sphere[vertex2 * 3 + 2] = pz + startZ;
				sphereColor[vertex2 * 3] = 255;
				sphereColor[vertex2 * 3 + 1] = 160;
				sphereColor[vertex2 * 3 + 2] = 166;

				pz = cos(tempnextta)*radius;
				py = sin(tempnextta)*sin(theta)*radius;
				px = sin(tempnextta)*cos(theta)*radius;

				int vertex3 = ++currentVert;
				sphere[vertex3 * 3] = px + startX;
				sphere[vertex3 * 3 + 1] = py + startY;
				sphere[vertex3 * 3 + 2] = pz + startZ;
				sphereColor[vertex3 * 3] = 255;
				sphereColor[vertex3 * 3 + 1] = 160;
				sphereColor[vertex3 * 3 + 2] = 166;
				
				pz = cos(tempnextta)*radius;
				py = sin(tempnextta)*sin(theta)*radius;
				px = sin(tempnextta)*cos(theta)*radius;

				int vertex4 = ++currentVert;
				sphere[vertex4 * 3] = px + startX;
				sphere[vertex4 * 3 + 1] = py + startY;
				sphere[vertex4 * 3 + 2] = pz + startZ;
				sphereColor[vertex4 * 3] = 255;
				sphereColor[vertex4 * 3 + 1] = 160;
				sphereColor[vertex4 * 3 + 2] = 166;

				pz = cos(tempta)*radius;
				py = sin(tempta)*sin(nextTheta)*radius;
				px = sin(tempta)*cos(nextTheta)*radius;

				int vertex5 = ++currentVert;
				sphere[vertex5 * 3] = px + startX;
				sphere[vertex5 * 3 + 1] = py + startY;
				sphere[vertex5 * 3 + 2] = pz + startZ;
				sphereColor[vertex5 * 3] = 255;
				sphereColor[vertex5 * 3 + 1] = 160;
				sphereColor[vertex5 * 3 + 2] = 166;

				pz = cos(tempnextta)*radius;
				py = sin(tempnextta)*sin(nextTheta)*radius;
				px = sin(tempnextta)*cos(nextTheta)*radius;

				int vertex6 = ++currentVert;
				sphere[vertex6 * 3] = px + startX;
				sphere[vertex6 * 3 + 1] = py + startY;
				sphere[vertex6 * 3 + 2] = pz + startZ;
				sphereColor[vertex6 * 3] = 255;
				sphereColor[vertex6 * 3 + 1] = 160;
				sphereColor[vertex6 * 3 + 2] = 166;
			}
		}

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		
		glVertexPointer(3, GL_FLOAT, 0, sphere);
		glColorPointer(3, GL_UNSIGNED_BYTE, 0, sphereColor);
		glDrawArrays(GL_TRIANGLES, 0, SPHERE_ARRAY_SIZE/3);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	void draw(const Matrix& viewMatrix)
	{
		m_fmodSystem->update();

		m_musicChannel->getSpectrum(m_spectrumLeft, SPECTRUM_SIZE, 0, FMOD_DSP_FFT_WINDOW_RECT);
		m_musicChannel->getSpectrum(m_spectrumRight, SPECTRUM_SIZE, 1, FMOD_DSP_FFT_WINDOW_RECT);
		std::cout << "left : " << m_spectrumLeft[0] << ", right : " << m_spectrumRight[0] << std::endl;

		// draw axis.
		//drawWorldOriginLines(viewMatrix);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDepthMask(false);
		// NOTE on OpenGL Matrix model:
		// Screen = Proj * View * Model
		// Model = TransformA(3rd) * TransformB(2nd) * TransformC(1st) (Trasnform could be Rotate, Scale, Translate, etc)
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE); // add blend
		Matrix viewSpaceMatrix = viewMatrix;
		glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
		drawOutsideSphere(30, 0, 0, 0);
		loadTexture("../media/glass.bmp", mTextureID[1]);
		
		m_rotation += 2;
		for (int i = 0; i < 16; i++)
		{
			Matrix rotate1 = Matrix::makeRotateMatrix(i*22.5f, Vector(0.0f, 1.0f, 0.0f));
			Matrix rotate2 = Matrix::makeRotateMatrix(m_rotation/2, Vector(0.0f, 1.0f, 0.0f));
			Matrix translate1 = Matrix::makeTranslationMatrix(0.0f,0.0f, 4.5f); 
			Matrix modelMatrix = rotate2 * rotate1 * translate1;

			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawRectLeftSpec2(0, 0, 0, i ,5);
			drawRectRightSpec2(0, 0, 0, i, 5);
		}

		for (int i = 0; i < 16; i++)
		{
			Matrix rotate1 = Matrix::makeRotateMatrix(i*22.5f, Vector(0.0f, 1.0f, 0.0f));
			Matrix rotate2 = Matrix::makeRotateMatrix(m_rotation, Vector(1.0f, 0.0f, 0.0f));
			Matrix translate1 = Matrix::makeTranslationMatrix(0.0f, 0.0f, 3.0f);
			Matrix modelMatrix = rotate2 * rotate1 * translate1;

			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawRectLeftSpec(0, 0, 0, i, 3 );
			drawRectRightSpec(0, 0, 0, i, 3 );
		}
		
		Matrix rotate1 = Matrix::makeRotateMatrix(90.0f,Vector(1.0f, 0.0f, 0.0f));

		for (int i = 0; i < 8; i++)
		{
			Matrix enlarge = Matrix::makeScaleMatrix(Vector(1.0f + m_spectrumLeft[i]*3, 1.0f + m_spectrumLeft[i]*3, 1.0f + m_spectrumLeft[i]*3));
			Matrix modelMatrix = enlarge * rotate1;
			Matrix viewSpaceMatrix = viewMatrix * modelMatrix;
			glLoadMatrixf((GLfloat*)viewSpaceMatrix.mVal);
			drawSphere(0.5, 0, 0, 0);
		}
		glDepthMask(true);
	}	
};

#endif
