#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Player.h"
#include "Obstacle.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <fmod.hpp>
#include <fmod_errors.h>

void ERRCHECK(FMOD_RESULT result);

class Application
{
protected:
	int m_method;

	Sprite*		m_sprite01;
	Sprite*		m_sprite02;
	Sprite*		m_sprite03;
	Sprite*		m_sprite04;
	Sprite*		m_sprite05;
	Sprite*		m_sprite06;

	//Player 1 is always local Player
	Player m_Player1;

	//Player 2 is always other Player
	Player m_Player2;

	//Obstacle 1
	Obstacle obs;

	GameObject WinLoseSprite;

	std::vector<Bullet> selfBullets; 
	std::vector<Bullet> othersBullets;
	
	//FMOD
	FMOD::System* m_fmodSystem;
	FMOD::Sound* m_music;
	FMOD::Channel *m_musicChannel;

	Vector m_lastReceivedPos;
	float m_lastReceivedRtt;
	double m_prevReceivedTime;
	double m_prevFireTime; //firerate
	bool m_gameStarted;
	Vector mousePos;

	void networkUpdate();

	void limitVelAndPos(GameObject* go);

public:
	
	Application();
	~Application();


	static Application& getInstance()
	{
		static Application app;
		return app;
	}

	void initFmod();
	
	void sendMyData(void);
	void OnReceivedOpponentData(float* data);
	void ShootBullet(Vector direction, bool bouncy);

	virtual void start();	
	virtual void update(double elapsedTime);
	virtual void draw();
	virtual void onKeyPressed(int key);
	virtual void onKeyReleased(int key);
	virtual void onKeyHold(int key);
	virtual void onMousePressed(int button);
	virtual void onMouseReleased(int button);
	virtual void onMouseHold(int button);
	virtual void onMouseMoved(double mousePosX, double mousePosY);
	
};

enum GAME_STATE
{
	LOBBY = 0,
	GAMESTARTED,
	VICTORY
};