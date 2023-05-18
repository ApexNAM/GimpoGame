#include "IntroScreen.h"

IntroScreen::IntroScreen()
{
}

IntroScreen::~IntroScreen()
{
}

void IntroScreen::Start()
{
	this->introLogo = LoadTexture("srcs/SkagoGames.png");
	this->frameRec = { 0.0f, 0.0f, (float)introLogo.width / 8, (float)introLogo.height };
	this->position = { 550.0f, 180.0f };
}

void IntroScreen::Update(CameraController* camera, GameManager* gameManager)
{
	framesCounter++;

	if (framesCounter >= (30 / frameSpeed) && currentFrame < 7)
	{
		camera->StartCameraShake(0.25f, 5.0f);

		framesCounter = 0;
		currentFrame++;

		if (currentFrame > 7)
		{
			currentFrame = 7;
		}

		frameRec.x = (float)currentFrame * (float)introLogo.width / 8;
	}

	if (currentFrame == 7)
	{
		nextIntroTime += GetFrameTime();

		if (nextIntroTime >= 2.0f)
		{
			gameManager->gameStates = gameManager->INTRO_SCREEN;
			nextIntroTime = 0.0f;
		}
	}
}

void IntroScreen::Draw()
{
	DrawTextureRec(introLogo, frameRec, position, WHITE);

	if (currentFrame == 7)
	{
		DrawText("SkagoGames", 450, 395.0f,70.0f, BLACK);
		DrawText("SkagoGames 2023. made in Skago.", 490, 575.0f, 20.0f, BLACK);
	}
}

void IntroScreen::UnLoad()
{
	UnloadTexture(introLogo);
}
