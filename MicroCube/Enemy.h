#pragma once
#include <raylib.h>
#include "GameObject.h"

class Enemy : public GameObject
{
private:
	int health = 50;
	bool isDead = false;
	bool isRight;
	float speed = GetRandomValue(2, 5);
	float nextFireTime = 0.0f;
	float randomFireRate = GetRandomValue(1.5f, 2.5f);
	float nextRespawnTime = 0.0f;
private:
	bool isFireMode = false;
public:
	Enemy();
	~Enemy();
public:
	void Start() override;
	void Update() override;
	void Draw() override;
public:
	void TakeDamage(int damage);
public:
	bool getFireMode() const { return isFireMode; }
	bool CheckDead() const { return isDead; }
	void TurnOff_FireMode() { isFireMode = false; }
};

