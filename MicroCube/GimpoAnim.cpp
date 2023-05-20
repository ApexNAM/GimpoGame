#include "GimpoAnim.h"

GimpoAnim::GimpoAnim()
{
}

GimpoAnim::~GimpoAnim()
{
}

void GimpoAnim::Start()
{
	this->gimpoAnim = LoadTexture("srcs/Images/gimpo_anim_map.png");
	this->frameRec = { 0.0f, 0.0f, (float)gimpoAnim.width / 8, (float)gimpoAnim.height };
	this->position = { 540.0f, 380.0f };
}

void GimpoAnim::Update()
{
	framesCounter++;

	if (framesCounter >= (60 / frameSpeed))
	{
		framesCounter = 0;
		currentFrame++;

		if (currentFrame > 7)
		{
			currentFrame = 0;
		}

		frameRec.x = (float)currentFrame * (float)gimpoAnim.width / 8;
	}
}

void GimpoAnim::Draw()
{
	DrawTextureRec(gimpoAnim, frameRec, position, WHITE);
}

void GimpoAnim::UnLoad()
{
	UnloadTexture(gimpoAnim);
}
