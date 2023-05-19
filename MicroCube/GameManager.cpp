#include "GameManager.h"

GameManager::GameManager()
{
	this->ReturnScore();
}

GameManager::~GameManager()
{
}

void GameManager::Update(CameraController* camera)
{
	limitTime -= GetFrameTime();

	if (limitTime <= 0.0f)
	{
		camera->StartCameraShake(0.25f, 8.0f);
		gameStates = GAME_OVER;
		limitTime = 0.0f;
	}
}

void GameManager::ReadyTime()
{
	startTime += GetFrameTime();

	if (startTime >= 3.0f)
	{
		gameStates = IN_GAME;
		startTime = 0.0f;
	}
}

void GameManager::AddScore(int takeScore)
{
	this->score += takeScore;
}

void GameManager::ReturnScore()
{
	this->level = 1;
	this->score = 0;
	this->limitTime = MAX_LIMIT_TIME;
}

void GameManager::NextLevel()
{
	this->level += 1;
	this->limitTime = MAX_LIMIT_TIME;
}
