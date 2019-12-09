#include "Player.h"

#define RESOLUTION_WIDTH 800
#define RESOLUTION_HEIGHT 600

Player::Player()
{
	m_health = 5;
	setPos(0.0f, 0.0f);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(1.0f, 1.0f);
	setOriScale(Vector(0.75f, 0.75f, 0.75f));
	setRotation(0.5f);
	radius = 20;
	setBlendMode(BlendMode::ADDITIVE);
}

Player::Player(Sprite* sprite)
{
	m_health = 5;
	m_sprite = sprite;
	setPos(0.0f, 0.0f);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(1.0f, 1.0f);
	setOriScale(Vector(0.75f, 0.75f, 0.75f));
	radius = 20;
	setBlendMode(BlendMode::ADDITIVE);
}

Player::Player(Sprite* sprite, float x, float y)
{
	m_health = 5;
	m_sprite = sprite;
	setPos(x, y);
	setColor(1.0f, 1.0f, 1.0f, 1.0f);
	setScale(1.0f, 1.0f);
	setOriScale(Vector(0.75f, 0.75f, 0.75f));
	radius = 20;
	setBlendMode(BlendMode::ADDITIVE);
}

void Player::setUISprite(Sprite* hpSprite)
{
	m_hpSprite = hpSprite;
}

//check border
void Player::borderCheck()
{
	if (getPos().mVal[0] + radius >= RESOLUTION_WIDTH && getVelocity().mVal[0] > 0.0f)
	{
		setVelocity(Vector(0.0f, getVelocity().mVal[1], 0.0f));
		setPos(Vector(RESOLUTION_WIDTH - radius,getPos().mVal[1],0.0f));
	}
	else if (getPos().mVal[0] - radius < 0.0f && getVelocity().mVal[0] < 0.0f)
	{
		setVelocity(Vector(0.0f, getVelocity().mVal[1], 0.0f));
		setPos(Vector(radius, getPos().mVal[1], 0.0f));
	}

	if (getPos().mVal[1] + radius >= RESOLUTION_HEIGHT && getVelocity().mVal[1] > 0.0f)
	{
		setVelocity(Vector(getVelocity().mVal[0], 0.0f , 0.0f));
		setPos(Vector(getPos().mVal[0], RESOLUTION_HEIGHT - radius, 0.0f));
	}
	else if (getPos().mVal[1] - radius < 0.0f && getVelocity().mVal[1] < 0.0f)
	{
		setVelocity(Vector(getVelocity().mVal[0], 0.0f, 0.0f));
		setPos(Vector(getPos().mVal[0], radius, 0.0f));
	}
}

int Player::rectCollision(Player* go1, Bullet* go2)
{
	if (go1->getPos().mVal[0] + go1->m_sprite->getWidth() / 2 < go2->getPos().mVal[0] - go2->m_sprite->getWidth() / 2) return 1; //go1 left
	if (go1->getPos().mVal[0] - go1->m_sprite->getWidth() / 2 > go2->getPos().mVal[0] + go2->m_sprite->getWidth() / 2) return 2; //go1 right
	if (go1->getPos().mVal[1] + go1->m_sprite->getHeight() / 2 < go2->getPos().mVal[1] - go2->m_sprite->getHeight() / 2) return 3; //go1 btm
	if (go1->getPos().mVal[1] - go1->m_sprite->getHeight() / 2 > go2->getPos().mVal[1] + go2->m_sprite->getHeight() / 2) return 4; //go1 top
	return 0;
}

bool Player::circleCollision(Bullet* go)
{
	float collided = radius + go->radius;
	Vector vec = getPos() - go->getPos();
	float distance = sqrtf((vec.mVal[0] * vec.mVal[0]) + (vec.mVal[1] * vec.mVal[1]));
	if (collided > distance)
	{
		std::cout << "Collided" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::circleCollision(Player* go)
{
	float collided = radius + go->radius;
	Vector vec = getPos() - go->getPos();
	float distance = sqrtf((vec.mVal[0] * vec.mVal[0]) + (vec.mVal[1] * vec.mVal[1]));
	if (collided > distance)
	{
		go->setVelocity(go->getVelocity() + (vec * -1.0f) * 20.0f);
		setVelocity(getVelocity() + (vec * 1.0f) * 20.0f);
		return true;
	}
	else
	{
		return false;
	}
}

bool Player::circleCollision(Obstacle* go)
{
	if (go->isSquare)
	{
		float collided = radius + go->m_sprite->getWidth();
		Vector vec = getPos() - go->getPos();
		float distance = sqrtf((vec.mVal[0] * vec.mVal[0]) + (vec.mVal[1] * vec.mVal[1]));
		if (collided > distance)
		{
			go->setVelocity(go->getVelocity() + (vec * -1.0f) * 1.0f);
			setVelocity(getVelocity() + (vec * 1.0f) * 20.0f);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float collided = radius + go->radius;
		Vector vec = getPos() - go->getPos();
		float distance = sqrtf((vec.mVal[0] * vec.mVal[0]) + (vec.mVal[1] * vec.mVal[1]));
		if (collided > distance)
		{
			setVelocity(getVelocity() + (vec * 1.0f) * 1.0f);
			return true;
		}
		else
		{
			return false;
		}
	}	
}

void Player::ShowHealth()
{
	Vector currentPos = getPos();
	Color c;
	switch(m_health)	
	{
	case 1 :
		c = Color(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 2 :
		c = Color(1.0f, 0.55f, 0.0f, 1.0f);
		break;
	case 3:
		c = Color(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 4:
		c = Color(0.5f, 1.0f, 0.0f, 1.0f);
		break;
	case 5:
		c = Color(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	}
	
	m_hpSprite->draw(Vector(currentPos.mVal[0], currentPos.mVal[1], 0.0f), c, Vector(1.0f, 1.0f, 1.0f), 0.0f , ADDITIVE);
}

void Player::setHealth(int hp)
{
	m_health = hp;
}

int Player::getHealth()
{
	return m_health;
}

void Player::draw()
{
	GameObject::draw();
	ShowHealth();
}

void Player::update(double elapsedTime)
{
	GameObject::update(elapsedTime);
	borderCheck();
	if (m_scale.mVal[0] > m_originalScale.mVal[0])
	{
		m_scale -= Vector(0.01f, 0.01f, 0.01f);
	}
}

Player::~Player()
{

}