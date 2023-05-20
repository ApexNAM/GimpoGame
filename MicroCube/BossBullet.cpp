#include "BossBullet.h"

BossBullet::BossBullet()
{
	this->w = 32;
	this->h = 32;
}

BossBullet::BossBullet(float x, float y)
{
	this->x = x;
	this->y = y;

	this->w = 15;
	this->h = 45;
}

BossBullet::~BossBullet()
{
}

void BossBullet::Start()
{
}

void BossBullet::Update()
{
	if (this->y > GetScreenHeight())
		isDestroyed = true;
	else
		this->y += 20.0f;
}

void BossBullet::Draw()
{
	DrawRectangle(this->x, this->y, this->w, this->h, DARKBROWN);
}

bool BossBullet::onCollisionEnter(GameObject* targetObject)
{
	if (targetObject->getX() + targetObject->getW() > this->x && targetObject->getX() < this->x + this->w &&
		targetObject->getY() + targetObject->getH() > this->y && targetObject->getY() < this->y + this->h)
	{
		this->isDestroyed = true;
		return true;
	}

	return false;
}
