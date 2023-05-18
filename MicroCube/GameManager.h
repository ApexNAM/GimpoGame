#pragma once
#include <vector>

class GameManager
{
public:
	enum GameStates
	{
		INTRO_SCREEN,
		MAIN_MENU,
		IN_GAME,
		GAME_OVER
	};
public:
	GameManager();
	~GameManager();
	
	GameStates gameStates = INTRO_SCREEN;
private:
	int score;
public:
	void AddScore(int takeScore);
	void ReturnScore();
	int getScore() const { return score; }
};

