#include <raylib.h>

#pragma once
class CameraController
{
private:
	Camera2D camera;
private:
	bool isCameraShaking = false;
	float shakeDuration = 0.0f;
	float shakeIntensity = 0.0f;
public:
	CameraController();
	~CameraController();

	Camera2D currentCamera() const { return camera; }
	void UpdateCameraShake();
	void StartCameraShake(float duration, float intensity);
};

