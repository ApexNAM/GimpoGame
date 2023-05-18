#include "GameObject.h"

GameObject::GameObject()
{
	this->x = 0;
	this->y = 0;

	this->w = 20;
	this->h = 20;

	this->tag = "default";
}

GameObject::GameObject(float sx, float sy, int sw, int sh)
{
	this->x = sx;
	this->y = sy;

	this->w = sw;
	this->h = sh;
}

GameObject::~GameObject()
{
}

void GameObject::Start()
{
}

void GameObject::Update()
{
}

void GameObject::Draw()
{
}
