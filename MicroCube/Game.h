#include <raylib.h>
#include <iostream>
#include <vector>

#include "IntroScreen.h"
#include "GameManager.h"
#include "Player.h"
#include "GameObject.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Boss.h"
#include "BossBullet.h"
#include "Bullet.h"
#include "CameraController.h"
#include "GimpoAnim.h"


#pragma once
class Game
{
private:
	bool isRunning = true;
	float nextTime = 0.0f;
	int nextSpawnCount = 1;
private:
	Texture2D kimpo_TEX = LoadTexture("/srcs/CI.png");
	Texture2D kimpo_Metro = LoadTexture("/srcs/GimpoMetro.png");
	Texture2D kimpo_City[3] =
	{
		LoadTexture("/srcs/Images/GimpoCity1.png"),
		LoadTexture("/srcs/Images/GimpoCity2.png"),
		LoadTexture("/srcs/Images/GimpoCity3.png")
	};

	Texture2D ClearCity = LoadTexture("/srcs/Images/GundomCity.png");

	int rndImage = GetRandomValue(1, 3);
	int rndKimpoCity = GetRandomValue(0, 2);
private:
	GameManager gameManager = GameManager();
	IntroScreen introScreen = IntroScreen();
	CameraController cameraController = CameraController();
	Boss boss = Boss();

	Player player = Player();
	GimpoAnim gimpoAnim = GimpoAnim();

	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Bullet>> bullets;
	std::vector<std::shared_ptr<EnemyBullet>> enemyBullets;
	std::vector<std::shared_ptr<BossBullet>> bossBullets;
private: // 김포 로고 변수들
	float gimpo_Y = -1200;
	float gimpo_T_Y = 1200;

	float commandTEXT = 1200;

private:
	const int widthScreen = 1280;
	const int heightScreen = 720;

	const std::string gameName = "Gimpo Game";
public:
	Game();
	~Game();
public:
	void Init();
	void Run();
private:
	void Update();
	void Render();
private:
	void ToggleFullscreenController();
	void InGame();
	void InGameDraw();
private:
	void SpawnBullet(bool isUpper);
	void SpawnEnemy(int len);
	void AllClear();
	void NextClear();
private:
	float Lerp(float target, float pos, float percent)
	{
		return (1 - percent) * target + percent * pos;
	}
};

