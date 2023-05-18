#include "GameManager.h"

GameManager::GameManager()
{
	this->score = 0;
}

GameManager::~GameManager()
{
}

void GameManager::AddScore(int takeScore)
{
	this->score += takeScore;
}

void GameManager::ReturnScore()
{
	this->score = 0;
}
