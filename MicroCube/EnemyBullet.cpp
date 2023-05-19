#include "EnemyBullet.h"

EnemyBullet::EnemyBullet()
{
	this->w = 10;
	this->h = 10;
}

EnemyBullet::EnemyBullet(float x, float y, bool isDown)
{
	this->x = x;
	this->y = y;

	this->w = 5;
	this->h = 20;

	this->isDown = isDown;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Start()
{
}

void EnemyBullet::Update()
{
	if (this->isDown)
	{
		if (this->y > GetScreenHeight())
			isDestroyed = true;
		else
			this->y += 20.0f;
	}
	else 
	{
		if (this->y < 0.0f)
			isDestroyed = true;
		else
			this->y -= 20.0f;
	}
}

void EnemyBullet::Draw()
{
	DrawRectangle(this->x, this->y, this->w, this->h, RED);
}

bool EnemyBullet::onCollisionEnter(GameObject* targetObject)
{
	if (targetObject->getX() + targetObject->getW() > this->x && targetObject->getX() < this->x + this->w &&
		targetObject->getY() + targetObject->getH() > this->y && targetObject->getY() < this->y + this->h)
	{
		this->isDestroyed = true;
		return true;
	}

	return false;
}
