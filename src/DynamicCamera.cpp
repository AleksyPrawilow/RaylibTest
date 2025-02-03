//
// Created by Alexey Pravilov on 2.02.25.
//

#include "../include/DynamicCamera.h"

#include <iostream>

DynamicCamera::DynamicCamera(Camera2D * p_camera, Entity * p_target)
{
  camera = p_camera;
  target = p_target;
}

DynamicCamera::~DynamicCamera()=default;

Camera2D * DynamicCamera::getCamera() const
{
  return camera;
}

void DynamicCamera::update(float delta)
{
  camera->target = target->getPositionRay();
  shakeVector.x = std::lerp(shakeVector.x, 0.0f, 12.0f * delta);
  shakeVector.y = std::lerp(shakeVector.y, 0.0f, 12.0f * delta);
  camera->offset = Vector2(1280 -(GetMousePosition().x + 640) / 2 + shakeVector.x, 720 -(GetMousePosition().y + 360) / 2 + shakeVector.y);
  if (isShaking)
  {
    elapsedTime += delta;
    elapsedTimeFrequency += delta;
    if (elapsedTimeFrequency > frequency)
    {
      std::uniform_real_distribution<float> dist(-amplitude, amplitude);
      float randomFloat = dist(generator);
      shakeVector.x += dist(generator);
      shakeVector.y += dist(generator);
      elapsedTimeFrequency = 0.0f;
    }
    if (elapsedTime > duration)
    {
      isShaking = false;
      elapsedTime = 0.0f;
    }
  }
}

void DynamicCamera::createShake(float p_amplitude, float p_frequency, float p_duration, int priority)
{
  isShaking = true;
  elapsedTime = 0.0f;
  elapsedTimeFrequency = 0.0f;
  amplitude = p_amplitude;
  frequency = p_frequency;
  duration = p_duration;
}
