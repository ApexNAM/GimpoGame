#include <raylib.h>
#include <iostream>
#include <vector>

#include "GameManager.h"
#include "Player.h"
#include "GameObject.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Bullet.h"
#include "CameraController.h"


#pragma once
class Game
{
private:
	bool isRunning = true;
	float nextTime = 0.0f;
	Texture2D kimpo_TEX = LoadTexture("/srcs/CI.png");
private:
	GameManager gameManager = GameManager();
	CameraController cameraController = CameraController();

	Player player = Player();
	std::vector<std::shared_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Bullet>> bullets;
	std::vector<std::shared_ptr<EnemyBullet>> enemyBullets;
private: // ���� �ΰ� ������
	float gimpo_Y = -1200;
	float gimpo_T_Y = 1200;

private:
	const int widthScreen = 1280;
	const int heightScreen = 720;

	const std::string gameName = "Gimpo TopDown";
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
private:
	float Lerp(float target, float pos, float percent)
	{
		return (1 - percent) * target + percent * pos;
	}
};

