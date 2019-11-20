#pragma once

#include "vector.h"
#include "Sprite.h"

enum enumBlend
{

};

class GameObject
{
private:
	Sprite* m_sprite;

	Vector m_position;
	float m_rotation;
	float m_scale;
	Color m_color;
	enumBlend m_blendMode;

public:
	GameObject();
	GameObject(Sprite* sprite);

	void setPos(Vector pos);
	const Vector& getPos();
	void setRotation(float rotate);
	float getRotation();
	void setScale(float scale);
	float getScale();
	void setSprite(Sprite* sprite);
	Sprite* getSprite();
	void setColor(const Color& color);
	const Color& getColor();

	void Draw();
	virtual void update();
};
