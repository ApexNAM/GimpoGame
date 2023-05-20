#pragma once
#include "GameObject.h"
class BossBullet : public GameObject
{
private:
	bool isDown = true;
public:
	BossBullet();
	BossBullet(float x, float y);
	~BossBullet();
public:
	void Start() override;
	void Update() override;
	void Draw() override;
public:
	bool onCollisionEnter(GameObject* targetObject);
};

