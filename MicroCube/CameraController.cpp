#include "CameraController.h"

CameraController::CameraController()
{
	camera.target = { 0, 0 };
	camera.offset = { 0, 0 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
}

CameraController::~CameraController()
{
}

void CameraController::UpdateCameraShake()
{
	if (isCameraShaking)
	{
		camera.offset.x = GetRandomValue(-shakeIntensity, shakeIntensity);
		camera.offset.y = GetRandomValue(-shakeIntensity, shakeIntensity);
		shakeDuration -= GetFrameTime();

		if (shakeDuration <= 0.0f)
		{
			shakeDuration = 0.0f;
			shakeIntensity = 0.0f;
			isCameraShaking = false;
			camera.offset = { 0, 0 };
		}
	}
}

void CameraController::StartCameraShake(float duration, float intensity)
{
	this->shakeDuration = duration;
	this->shakeIntensity = intensity;
	isCameraShaking = true;
}
