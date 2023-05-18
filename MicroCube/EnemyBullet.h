#pragma once
#include "GameObject.h"
class EnemyBullet : public GameObject
{
public:
	EnemyBullet();
	EnemyBullet(float x, float y);
	~EnemyBullet();
public:
	void Start() override;
	void Update() override;
	void Draw() override;
public:
	bool onCollisionEnter(GameObject* targetObject);
};

