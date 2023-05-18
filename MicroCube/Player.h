#include <raylib.h>
#include "GameObject.h"
#pragma once

class Player
{
private:
	float x, y;
	int w, h;
	float vy, speed;
	int hp = 100;
	bool isDead = false;
	bool isGrounded = false;
	float nextDamageTime = 0.0f;
public:
	Player();
	Player(float sx, float sy, int sw, int sh);
	~Player();
public:
	void Start();
	void Update();
	void Draw();
public:
	void Jump();
	void DoubleJump(float power);
	void TakeDamage(int damage);
	void TakeHealth(int health);
	void ReturnHealth();
public:
	bool onCollisionDamage(GameObject* targetObject);
	bool onCollisionEnter(GameObject* targetObject, float targetPower);
public:
	int getHP() const { return this->hp; }
	float getX() const { return x; }
	float getY() const { return y; }
	bool CheckDead() const { return isDead; }
};

