#include "Application.h"
#include "stdafx.h"
	
Application::Application()
{

}

Application::Application(float crTime)
{
	currentTime = crTime;
	lastTime = crTime;
	frameCount = 0;
	fps = 0;
	deltaTime = 0;
}

void Application::start()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glDisable(GL_DEPTH_TEST);

	std::cout << "Application is started" << std::endl;

	//glGenTextures(TEXTURE_COUNT, GtextureID);

	//m_dummySprite = new Sprite();
	m_dummySprite = new Sprite("../media/testParticle.bmp");
	
	/*m_dummyGameObject = new GameObject(m_dummySprite);

	m_dummyGameObject->setPos(Vector(400.0f, 300.0f,0.0));
	m_dummyGameObject->setRotation(5.0f);
	m_dummyGameObject->setScale(1.0f);
	m_dummyGameObject->setColor(Color(1.0, 1.0, 0.0));*/
	m_dummyParticleSystem = new ParticleSystem(m_dummySprite);
	m_dummyParticleSystem->setPos(Vector(400.f, 300.0f, 0.0f));
	//std::cout << m_dummySprite << std::endl;
}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//m_dummySprite->draw(400.0, 300.0, 0.0, 1, Color(1.0, 1.0, 1.0));
	//m_dummyGameObject->Draw();
	m_dummyParticleSystem->draw();
	//m_dummySprite->draw(220, 400);

}

void Application::update(float crTime)
{
	currentTime = crTime;
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	m_dummyParticleSystem->update(deltaTime);
}