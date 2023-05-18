#include "Bullet.h"

Bullet::Bullet()
{
	this->Start();
}

Bullet::Bullet(float x, float y, bool isUpper)
{
	this->x = x;
	this->y = y;

	this->w = 8;
	this->h = 20;

	this->isUpper = isUpper;
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	this->w = 10;
	this->h = 20;

	this->tag = "Bullet";
}

void Bullet::Update()
{
	if (this->isUpper)
	{
		if (this->y <= 0.0f)
			this->isDestroyed = true;
		else
			this->y -= 25.0f;
	}
	else
	{
		if (this->y >= 720.0f)
			this->isDestroyed = true;
		else
			this->y += 25.0f;
	}

}

void Bullet::Draw()
{
	DrawRectangle(this->x, this->y, this->w, this->h, BLACK);
}

void Bullet::StartXY(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool Bullet::onCollisionEnter(GameObject* targetObject)
{
	if (targetObject->getX() + targetObject->getW() > this->x && targetObject->getX() < this->x + this->w &&
		targetObject->getY() + targetObject->getH() > this->y && targetObject->getY() < this->y + this->h)
	{
		this->isDestroyed = true;
		return true;
	}

	return false;
}
