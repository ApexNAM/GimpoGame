#include "Enemy.h"

Enemy::Enemy()
{
	this->Start();
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
	this->speed = GetRandomValue(3.0f, 5.0f);
	this->y = GetRandomValue(100, 700);


	this->health = 50;
	this->isDead = false;

	int rnd = GetRandomValue(0, 1);

	if (rnd == 0)
	{
		this->x = 0.0f;
		this->isRight = false;
	}
	else if (rnd == 1)
	{
		this->x = GetScreenWidth();
		this->isRight = true;
	}

	this->w = 40;
	this->h = 20;

	this->tag = "Enemy";
	this->isDestroyed = false;
}

void Enemy::Update()
{
	if (!this->isDead)
	{
		if (this->isRight)
		{
			this->x -= this->speed;

			if (this->x < 0.0f)
			{
				if (this->y <= 700.0f)
					this->y += 20;

				isRight = false;
			}

		}
		else
		{
			this->x += this->speed;

			if (this->x > GetScreenWidth())
			{
				if (this->y <= 700.0f)
					this->y += 20;

				isRight = true;
			}
		}

		if (GetTime() >= this->nextFireTime)
		{
			isFireMode = true;
			nextFireTime = GetTime() + randomFireRate;
		}
	}
	else
	{
		nextRespawnTime += GetFrameTime();

		if (nextRespawnTime >= 5.0f)
		{
			this->health = 50;
			isDead = false;

			nextRespawnTime = 0.0f;
		}
	}
}

void Enemy::Draw()
{
	DrawRectangle(this->x, this->y, this->w, this->h, BROWN);
}

void Enemy::TakeDamage(int damage)
{
	health -= damage;

	if (health <= 0)
		this->isDead = true;
}
