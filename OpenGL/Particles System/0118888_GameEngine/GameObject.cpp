#include "GameObject.h"

GameObject::GameObject()
{
	m_sprite = new Sprite();
}

GameObject::GameObject(Sprite* sprite)
{
	m_sprite = sprite;
	m_color = Color(1.0, 1.0, 1.0);
}

void GameObject::setPos(Vector pos)
{
	m_position = pos;
}

const Vector& GameObject::getPos()
{
	return m_position;
}

void GameObject::setRotation(float rotate)
{
	m_rotation = rotate;
}

float GameObject::getRotation()
{
	return m_rotation;
}

void GameObject::setScale(float scale)
{
	m_scale = scale;
}

float GameObject::getScale()
{
	return m_scale;
}

void GameObject::setSprite(Sprite* sprite)
{
	m_sprite = sprite;
}

Sprite* GameObject::getSprite()
{
	return m_sprite;
}

void GameObject::setColor(const Color& color)
{
	m_color = color;
}

const Color& GameObject::getColor()
{
	return m_color;
}

void GameObject::Draw()
{
	m_sprite->draw(m_position.mVal[0], m_position.mVal[1], m_rotation, m_scale, m_color);
}

void GameObject::update()
{

}