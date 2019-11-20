#pragma once
#include "GLFW/glfw3.h"
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleSystem.h"

class Application
{
private:
	Sprite* m_dummySprite;
	GameObject* m_dummyGameObject;
	ParticleSystem* m_dummyParticleSystem;

public:
	float currentTime;
	float lastTime;
	float frameCount;
	float fps;
	float deltaTime;

	//limit fps
	float targetFps = 30;
	float minDeltaTime = 1.0 / targetFps;

	Application();
	Application(float crTime);
	
	void start();
	void draw();
	void update(float crTime);
};