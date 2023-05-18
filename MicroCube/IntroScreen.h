#include <raylib.h>
#include "GameManager.h"
#include "CameraController.h"

#pragma once
class IntroScreen
{	
private:
	Texture2D introLogo = LoadTexture("/srcs/SkagoGames.png");
	Rectangle frameRec = { 0.0f, 0.0f, (float)introLogo.width / 8, (float)introLogo.height };
	Vector2 position = { 350.0f, 180.0f };
private:
	int currentFrame = 0;
	int framesCounter = 0;
	int frameSpeed = 4;
private:
	float nextIntroTime = 0.0f;
public:
	IntroScreen();
	~IntroScreen();

	void Start();
	void Update(CameraController* camera, GameManager* gameManager);
	void Draw();
	void UnLoad();
};

