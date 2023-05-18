#pragma once
#include <vector>

class GameManager
{
public:
	enum GameStates
	{
		SKAGO_GAMES_INTRO,
		INTRO_SCREEN,
		MAIN_MENU,
		IN_GAME,
		GAME_OVER
	};
public:
	GameManager();
	~GameManager();
	
	GameStates gameStates = SKAGO_GAMES_INTRO;
private:
	int score;
public:
	void AddScore(int takeScore);
	void ReturnScore();
	int getScore() const { return score; }
};

