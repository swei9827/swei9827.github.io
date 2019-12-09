#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "MyPhoton.h"

#define BULLET_SPEED 250.0f;
using namespace std;

// The higher networkFPS, the higher bandwidth requirement of your game.
// ** about 30FPS is common data sync rate for real time games
// ** slower-paced action games could use as low as 10 FPS

const float networkFPS = 20.0f;
const float gNetworkFrameTime = 1.0f/networkFPS;

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! : " << FMOD_ErrorString(result) << std::endl;
	}
}

Application::Application ()
{
	/*
	method 0 : without any interpolation or prediction (send/receive position only)
	method 1 : simple interpolation (send/receive position only)
	method 2 : prediction + interpolation 1 (send/receive position only, data saving hybrid method, 
											 the result is like in between method1 and method3)
	method 3 : prediction + interpolation 2 (send/receive position, velocity and acceleration information for more precise prediction, 
  											 3 times higher data bandwidth requirement compare with method 0-2, more responsive than method 2)
	*/

	m_method = 3;
}

Application::~Application ()
{	
}

void Application::start ()
{
	srand(time(0));

	m_gameStarted = false;
	initFmod();
	MyPhoton::getInstance().connect();

	m_sprite01 = new Sprite ("../media/Tank.bmp");
	m_sprite02 = new Sprite("../media/Bullet.bmp");
	m_sprite03 = new Sprite("../media/Health.bmp");
	m_sprite04 = new Sprite("../media/Obstacle.bmp");
	m_sprite05 = new Sprite("../media/Win.bmp");
	m_sprite06 = new Sprite("../media/Lose.bmp");

	m_Player1.setSprite(m_sprite01);
	m_Player1.setColor(Color(0.275, 0.5, 0.7, 1.0));
	m_Player1.setScale(Vector(0.75, 0.75, 0.75));
	m_Player1.setUISprite(m_sprite03);
	m_Player1.setPos(Vector(rand()%800,rand()%600,0));
	m_Player1.setBlendMode(ADDITIVE);

	m_Player2.setSprite(m_sprite01);
	m_Player2.setColor(Color(0.98, 0.5, 0.45, 1.0));
	m_Player2.setScale(Vector(0.75, 0.75, 0.75));
	m_Player2.setUISprite(m_sprite03);
	m_Player2.setPos(Vector(200, 200, 0));
	m_Player2.setBlendMode(ADDITIVE);

	obs.setSprite(m_sprite04);
	obs.setPos(400.f, 300.0f);
	obs.radius = 40;
	obs.isSquare = false;
	obs.setScale(Vector(2.0f, 2.0f, 1.0f));
	obs.setBlendMode(ADDITIVE);

	m_lastReceivedPos = m_Player2.getPos();
}

void Application::initFmod()
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
	result = m_fmodSystem->createStream("../media/Test.mp3", FMOD_SOFTWARE, 0, &m_music);
	ERRCHECK(result);

	//play the loaded mp3 music
	result = m_fmodSystem->playSound(FMOD_CHANNEL_FREE, m_music, false, &m_musicChannel);
	ERRCHECK(result);
}

void Application::sendMyData(void)
{
	Vector pos =  m_Player1.getPos();
	Vector vel = m_Player1.getVelocity();
	Vector acc = m_Player1.getAcceleration();
	float rtt = m_Player1.getRotation();
	MyPhoton::getInstance().sendMyData(pos.mVal[0], pos.mVal[1],
										vel.mVal[0], vel.mVal[1],
										acc.mVal[0], acc.mVal[1],
										rtt);
}

void Application::networkUpdate()
{
	static double prevTime = glfwGetTime();
	
	double time = glfwGetTime();
	if(time - prevTime >= gNetworkFrameTime) 
	{
		sendMyData();
		prevTime = time;
	}
}

void Application::limitVelAndPos(GameObject* go)
{
	if(go->getVelocity().length() > 200.0f)
	{
		Vector vec = go->getVelocity();
		vec.normalize();
		vec *= 200.0f;
		go->setVelocity(vec);
	}
}

void Application::update (double elapsedTime)
{
	MyPhoton::getInstance().run();

	if(!m_gameStarted)
		return;
	
	m_Player1.update(elapsedTime);
	m_Player1.setAcceleration(Vector(0.0f, 0.0f, 0.0f));
	limitVelAndPos(&m_Player1);
	
	networkUpdate();

	if(m_method == 0)
	{
		m_Player2.setPos(m_lastReceivedPos);
	}
	else if(m_method == 1)
	{
		m_Player2.setPos(m_Player2.getPos()*0.96f + m_lastReceivedPos*0.04f);
	}

	else if(m_method == 2)
	{
		m_Player2.update(elapsedTime);
		m_Player2.setAcceleration(Vector(0.0f, 0.0f, 0.0f));
		limitVelAndPos(&m_Player2);
	}
	else if(m_method == 3)
	{
		m_Player2.update(elapsedTime);

		//very slowly interpolate from on-going predicting pos to lastest received pos. Without this interpolation, the offset of opponent position will keep being accumulated. 
		m_Player2.setPos(m_Player2.getPos()*0.995f + m_lastReceivedPos*0.005f);
		m_Player2.setRotation(m_Player2.getRotation()*0.7f + m_lastReceivedRtt * 0.3f);
		limitVelAndPos(&m_Player2);
	}

	//delete passed local bullets
	for (int i = 0; i < selfBullets.size(); i++)
	{
		if (selfBullets[i].CheckBoundary())
		{
			selfBullets.erase(selfBullets.begin()+i);
		}
	}

	//update local bullets pos
	for (int i = 0; i < selfBullets.size(); i++)
	{
		selfBullets[i].update(elapsedTime);
	}

	//delete passed opponent bullets
	for (int i = 0; i < othersBullets.size(); i++)
	{
		if (othersBullets[i].CheckBoundary())
		{
			othersBullets.erase(othersBullets.begin() + i);
		}
	}

	//update opponent bullets pos
	for (int i = 0; i < othersBullets.size(); i++)
	{
		othersBullets[i].update(elapsedTime);
	}

	/*for (int i = 0; i < selfBullets.size(); i++)
	{
		if (m_Player2.rectCollision(&m_Player2, &selfBullets[i]) == 0)
		{
			selfBullets.erase(selfBullets.begin() + i);
			m_Player2.setHealth(m_Player2.getHealth() - 1);
		}
	}*/

	//check local bullet collison
	for (int i = 0; i < selfBullets.size(); i++)
	{
		if (selfBullets[i].circleCollision(&obs))
		{
			selfBullets[i].bounce++;
		}
		if (m_Player2.circleCollision(&selfBullets[i]))
		{
			selfBullets.erase(selfBullets.begin() + i);
			m_Player2.setScale(m_Player2.getScale() + Vector(0.2f,0.2f,0.2f));
			m_Player2.setHealth(m_Player2.getHealth() - 1);
			if (m_Player2.getHealth() <= 0)
			{
				WinLoseSprite.setSprite(m_sprite05);
				WinLoseSprite.setPos(400.0f, 100.0f);
				WinLoseSprite.setBlendMode(ADDITIVE);
				m_game
			}
		}
	}

	//check opponent bullet collision
	for (int i = 0; i < othersBullets.size(); i++)
	{
		if (othersBullets[i].circleCollision(&obs))
		{
			othersBullets[i].bounce++;
		}
		if (m_Player1.circleCollision(&othersBullets[i]))
		{
			othersBullets.erase(othersBullets.begin() + i);
			m_Player1.setHealth(m_Player1.getHealth() - 1);
			if (m_Player1.getHealth() <= 0)
			{
				WinLoseSprite.setSprite(m_sprite06);
				WinLoseSprite.setPos(400.0f, 100.0f);
				WinLoseSprite.setBlendMode(ADDITIVE);
			}
		}
	}

	m_Player1.circleCollision(&m_Player2);
	m_Player1.circleCollision(&obs);
	m_Player2.circleCollision(&obs);
}

void Application::draw()
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(!m_gameStarted)
		return;

	m_Player1.draw();
	m_Player2.draw();

	obs.draw();

	for (int i = 0; i < selfBullets.size(); i++)
	{
		selfBullets[i].draw();
	}
	for (int i = 0; i < othersBullets.size(); i++)
	{
		othersBullets[i].draw();
	}

	if (WinLoseSprite.m_sprite != NULL)
	{
		WinLoseSprite.draw();
	}
}


void Application::OnReceivedOpponentData(float* data)
{
	if(m_gameStarted == false)
	{
		m_gameStarted = true;
		m_Player2.setPos(Vector(data[0], data[1], 0));

		m_lastReceivedPos = m_Player2.getPos();
		m_prevReceivedTime = glfwGetTime();
		return;
	}

	if(m_method == 0 || m_method == 1)
	{
		m_lastReceivedPos = Vector(data[0], data[1], 0);
	}
	else if(m_method == 2)
	{
		double currentTime = glfwGetTime();
		double timeSinceLastReceive = currentTime - m_prevReceivedTime;

		if(timeSinceLastReceive >= gNetworkFrameTime*0.5f) //filter the noise
		{
			Vector targetPos = Vector(data[0], data[1], 0.0f);

			float length = (m_lastReceivedPos - targetPos).length() / timeSinceLastReceive;
			Vector goVec = targetPos - m_Player2.getPos();
			goVec.normalize();

			goVec = goVec * length;

			Vector finalVel = m_Player2.getVelocity()*0.6f + goVec *0.4f;
			m_Player2.setVelocity(finalVel);
		
			m_lastReceivedPos = targetPos;
			m_prevReceivedTime = currentTime;
		}
	}
	else if(m_method == 3)
	{
		if (data[0] >= 0.0f)
		{
			m_lastReceivedPos = Vector(data[0], data[1], 0);
			m_Player2.setVelocity(Vector(data[2], data[3], 0));
			m_Player2.setAcceleration(Vector(data[4], data[5], 0));
			m_lastReceivedRtt = data[6];
		}
		else if(data[0] < 0.0f)
		{
			Bullet bullet = Bullet(m_sprite02, data[1], data[2],data[6]);
			bullet.setColor(1.0f, 0.4f, 0.4f, 1.0f);
			bullet.Target(250.0f, Vector(data[3],data[4],0.0f), data[5]);
			othersBullets.push_back(bullet);
		}		
	}
}


void Application::onKeyPressed (int key)
{

}

void Application::onKeyReleased (int key)
{
}

void Application::onKeyHold (int key)
{
	if(!m_gameStarted)
		return;
	
	if (key == GLFW_KEY_W)
	{
		m_Player1.setAcceleration(m_Player1.getAcceleration()+Vector(0.0f, 300.0f, 0.0f));
	}
	if(key == GLFW_KEY_A)
	{
		m_Player1.setAcceleration(m_Player1.getAcceleration()+Vector(-300.0f, 0.0f, 0.0f));
	}
	if(key == GLFW_KEY_S)
	{
		m_Player1.setAcceleration(m_Player1.getAcceleration()+Vector(0.0f, -300.0f, 0.0f));
	}
	if(key == GLFW_KEY_D)
	{
		m_Player1.setAcceleration(m_Player1.getAcceleration()+Vector(300.0f, 0.0f, 0.0f));
	}
	
	float x = mousePos.mVal[0] - m_Player1.getPos().mVal[0];
	float y = mousePos.mVal[1] - m_Player1.getPos().mVal[1];
	float radian = atan2f(y, x);
	m_Player1.setRotation(radian);
	/*if(key == GLFW_KEY_W)
	{
		m_object1.setVelocity(Vector(0.0f, 400.0f, 0.0f));
	}
	if(key == GLFW_KEY_A)
	{
		m_object1.setVelocity(Vector(-400.0f, 0.0f, 0.0f));
	}
	if(key == GLFW_KEY_S)
	{
		m_object1.setVelocity(Vector(0.0f, -400.0f, 0.0f));
	}
	if(key == GLFW_KEY_D)
	{
		m_object1.setVelocity(Vector(400.0f, 0.0f, 0.0f));
	}
	*/
}

void Application::onMousePressed(int button)
{
	// bullet cooldown , the lower the value, the faster the reload
	float bulletCooldown = 0.4f;
	float bouncingBulletCooldown = 1.2f;
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		double currentTime = glfwGetTime();
		if (m_prevFireTime + bulletCooldown <= currentTime)
		{
			m_prevFireTime = currentTime;
			ShootBullet(mousePos,false);
		}		
	}
	if (button == GLFW_MOUSE_BUTTON_2)
	{
		double currentTime = glfwGetTime();
		if (m_prevFireTime + bouncingBulletCooldown <= currentTime)
		{
			m_prevFireTime = currentTime;
			ShootBullet(mousePos, true);
		}
	}
}

void Application::onMouseReleased (int button)
{

}

void Application::onMouseHold (int button)
{

}

void Application::onMouseMoved (double mousePosX, double mousePosY)
{
	mousePos = Vector(mousePosX, 600.0f - mousePosY,0.0);
	float x = mousePosX - m_Player1.getPos().mVal[0] ;
	float y = (600.0f - mousePosY) - m_Player1.getPos().mVal[1] ;
	float radian = atan2f(y, x);
	m_Player1.setRotation(radian);
}

void Application::ShootBullet(Vector target, bool bouncy)
{
	float x = target.mVal[0] - m_Player1.getPos().mVal[0] ;
	float y = target.mVal[1] - m_Player1.getPos().mVal[1];

	Vector vec = Vector(x, y, 0.0);
	vec.normalize();
	float radian = atan2f(y, x);

	Bullet bullet = Bullet(m_sprite02, m_Player1.getPos().mVal[0], m_Player1.getPos().mVal[1], bouncy);
	
	bullet.Target(250.0f,vec,radian);
	selfBullets.push_back(bullet);

	MyPhoton::getInstance().sendMyBullet(Vector(m_Player1.getPos().mVal[0], m_Player1.getPos().mVal[1],0.0f),vec,radian,bouncy);
}
