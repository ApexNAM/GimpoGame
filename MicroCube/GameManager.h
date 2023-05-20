#pragma once

#include <raylib.h>
#include <vector>
#include "CameraController.h"

#define MAX_LIMIT_TIME 60.0f

class GameManager
{
public:
	enum GameStates
	{
		SKAGO_GAMES_INTRO,
		INTRO_SCREEN,
		MAIN_MENU,
		TUTORAL,
		READY,
		IN_GAME,
		GAME_OVER,
		GAME_CLEAR,
		GAME_CLEAR_ALL
	};
public:
	GameManager();
	~GameManager();
	
	GameStates gameStates = SKAGO_GAMES_INTRO;
private:
	int score;
	int level = 1;
	float limitTime = MAX_LIMIT_TIME;
private:
	float startTime = 0.0f;
public:
	void Update(CameraController* camera);
	void ReadyTime();
public:
	void AddScore(int takeScore);
	void ReturnScore();
	void NextLevel();
public:
	int getScore() const { return score; }
	int getLimitTime() const { return (int)limitTime; }
	int getLevelIDX() const { return level; }
};

