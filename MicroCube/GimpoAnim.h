#include <raylib.h>

#pragma once
class GimpoAnim
{
private:
	Texture2D gimpoAnim = LoadTexture("/srcs/gimpo_anim_map.png");;
	Rectangle frameRec = { 0.0f, 0.0f, (float)gimpoAnim.width / 8, (float)gimpoAnim.height };
	Vector2 position = { 350.0f, 180.0f };
private:
	int currentFrame = 0;
	int framesCounter = 0;
	int frameSpeed = 16;
public:
	GimpoAnim();
	~GimpoAnim();
public:
	void Start();
	void Update();
	void Draw();
	void UnLoad();
};

