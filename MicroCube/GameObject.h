#include <raylib.h>
#include <iostream>

#pragma once
class GameObject
{
protected:
	float x, y;
	int w, h;
	float zIndex;
	std::string tag = "default";
	bool isDestroyed = false;
public:
	GameObject();
	GameObject(float sx, float sy, int sw, int sh);
	virtual ~GameObject();
public:
	virtual void Start();
	virtual void Update();
	virtual void Draw();
public:
	float getX() const { return this->x; }
	float getY() const { return this->y; }

	int getW() const { return this->w; }
	int getH() const { return this->h; }

	std::string Tag() const { return this->tag; }
	bool IsDestroyed() const { return isDestroyed; }

public:
	void SetYUP(float upY) { this->y -= upY; }
	void SetYDown(float downY) { this->y += downY; }
};

