#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::Start()
{
	this->isDead = false;

	this->x = 500;
	this->y = 0;

	this->w = 256;
	this->h = 256;

	this->speed = 300.0f;
	this->vy = -this->speed;

	clearSound = LoadSound("srcs/Sounds/clap.wav");
}

void Boss::Update()
{
	if (!this->isDead)
	{
		if (!this->isRight)
		{
			this->x -= 5.0f;

			if (this->x < 100)
				this->isRight = true;
		}
		else 
		{
			this->x += 5.0f;

			if (this->x > 1000)
				this->isRight = false;
		}

		if (GetTime() >= nextFireTime)
		{
			isFire = true;
			nextFireTime = GetTime() + 0.5f;
		}
	}
	else
	{
		this->y += this->vy * GetFrameTime();
		this->vy += this->speed * GetFrameTime();
	}
}

void Boss::Draw()
{
	if (!this->isDead)
		DrawRectangle(this->x, this->y, this->w, this->h, BROWN);
}

void Boss::Reset()
{
	this->isDead = false;

	this->x = 500;
	this->y = 0;

	this->w = 256;
	this->h = 256;
}

void Boss::UnLoad()
{
	UnloadSound(this->clearSound);
}

void Boss::TakeDamage_Boss(int dmaage)
{
	this->y += dmaage;

	if (this->y >= 250.0f)
	{
		this->isDead = true;
	}
}
