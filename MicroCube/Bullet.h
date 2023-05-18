#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
private:
	bool isUpper;
public:
	Bullet();
	Bullet(float x, float y, bool isUpper);
	~Bullet();
public:
	void Start() override;
	void Update() override;
	void Draw() override;
public:
	void StartXY(float x, float y);
	bool onCollisionEnter(GameObject* targetObject);
	bool gisUpper() const { return isUpper; }
};

