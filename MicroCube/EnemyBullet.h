#pragma once
#include "GameObject.h"
class EnemyBullet : public GameObject
{
private:
	bool isDown = true;
public:
	EnemyBullet();
	EnemyBullet(float x, float y, bool isDown);
	~EnemyBullet();
public:
	void Start() override;
	void Update() override;
	void Draw() override;
public:
	bool onCollisionEnter(GameObject* targetObject);
};

