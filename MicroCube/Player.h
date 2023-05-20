#include <raylib.h>
#include "GameObject.h"
#include "GameManager.h"

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
private:
	Sound gunFireSound = LoadSound("/srcs/Sounds/fire.wav");
	Sound jumpSound = LoadSound("/srcs/Sounds/JumpSound.wav");
	Sound hitSound = LoadSound("/srcs/Sounds/Hit.wav");
	Sound clapSound = LoadSound("/srcs/Sounds/clap.wav");
	Sound clapSound2 = LoadSound("/srcs/Sounds/clap2.wav");
public:
	Player();
	Player(float sx, float sy, int sw, int sh);
	~Player();
public:
	void Start();
	void Update(GameManager* gameManager);
	void Draw();
	void UnLoad();
public:
	void Jump();
	void DoubleJump(float power);
	void TakeDamage(int damage);
	void TakeHealth(int health);
	void ReturnHealth();
	void FireSoundPlay();
public:
	bool onCollisionDamage(GameObject* targetObject);
	bool onCollisionEnter(GameObject* targetObject, float targetPower);
public:
	int getHP() const { return this->hp; }
	float getX() const { return x; }
	float getY() const { return y; }
	bool CheckDead() const { return isDead; }
};

