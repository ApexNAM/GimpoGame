#pragma once
#include "GameObject.h"
#include "GameManager.h"
#include <raylib.h>

class Boss : public GameObject
{
private:
	bool isDead = false;
	bool isRight = false;
	float vy, speed;
private:
	bool isFire = false;
	float nextFireTime = 0.0f;
private:
	Sound clearSound = LoadSound("/srcs/Sounds/clap2.wav");
public:
	Boss();
	~Boss();
public:
	void Start() override;
	void Update() override;
	void Draw() override;
	void Reset();
	void UnLoad();
	void PlaySoundClear() { PlaySound(this->clearSound); }
public:
	void TakeDamage_Boss(int dmaage);
	void SetFireMode_Off() { isFire = false; }

	bool isFireModeEnabled() const { return isFire; }
	bool getIsDead() const { return isDead; }
};

