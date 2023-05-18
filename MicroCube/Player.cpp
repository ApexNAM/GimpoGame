#include "Player.h"

Player::Player()
{
	this->x = GetRandomValue(0, 1280);
	this->y = 700;

	this->w = 20;
	this->h = 20;
	
	this->speed = 300.0f;
	this->vy = -this->speed;
}

Player::Player(float sx, float sy, int sw, int sh)
{
	this->x = sx;
	this->y = sy;

	this->w = sw;
	this->h = sh;

	this->speed = 300.0f;
	this->vy = -this->speed;
}

Player::~Player()
{
}

void Player::Start()
{
	this->isDead = false;
	this->isGrounded = true;

	this->x = GetRandomValue(0, 1280);
	this->hp = 100;
}

void Player::Update()
{

	if (this->y < 0.0f)
	{
		this->y = 0;
		this->hp = 0;
		this->isDead = true;
	}
	else if (this->y > (GetScreenHeight() - 20))
	{
		this->y = (GetScreenHeight() - 20);
	}

	if (!isGrounded)
	{
		this->y += this->vy * GetFrameTime();
		this->vy += this->speed * GetFrameTime();

		if (this->y >= (GetScreenHeight() - 20))
		{
			this->y = (GetScreenHeight() - 20);
			this->vy = -this->speed;

			this->isGrounded = true;
		}
	}
	else
	{
		if (GetTime() >= nextDamageTime)
		{
			this->TakeDamage(1);
			nextDamageTime = GetTime() + 0.5f;
		}
	}

	if (!isDead)
	{
		if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && this->x > 0.0f)
			this->x -= 5.0f;
		else if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && this->x < GetScreenWidth())
			this->x += 5.0f;

		if (IsKeyPressed(KEY_SPACE) && isGrounded)
			this->Jump();
	}
}

void Player::Draw()
{
	if (!this->isDead)
		DrawRectangle(this->x, this->y, this->w, this->h, BLACK);
}

void Player::Jump()
{
	this->y -= 500.0f * GetFrameTime();
	this->isGrounded = false;
}

void Player::DoubleJump(float power)
{
	this->y += this->vy + power;
	this->isGrounded = false;
}

void Player::TakeDamage(int damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
	{
		this->hp = 0;
		isDead = true;
	}
}

void Player::TakeHealth(int health)
{
	this->hp += health;

	if (this->hp >= 100)
	{
		this->hp = 100;
	}
}

void Player::ReturnHealth()
{
	this->hp = 100;
	this->isDead = false;

	this->isGrounded = true;

	this->x = GetRandomValue(0, 1280);
	this->y = 700;

	this->speed = 300.0f;
	this->vy = -this->speed;
}

bool Player::onCollisionDamage(GameObject* targetObject)
{
	if (targetObject->getX() + targetObject->getW() > this->x && targetObject->getX() < this->x + this->w &&
		targetObject->getY() + targetObject->getH() > this->y && targetObject->getY() < this->y + this->h)
	{
		return true;
	}

	return false;
}

bool Player::onCollisionEnter(GameObject* targetObject, float targetPower)
{
	if (targetObject->getX() + targetObject->getW() > this->x && targetObject->getX() < this->x + this->w &&
		targetObject->getY() + targetObject->getH() > this->y && targetObject->getY() < this->y + this->h)
	{
		this->vy = -this->speed;

		this->DoubleJump(targetPower);
		return true;
	}

	return false;
}
