//
// Created by Alexey Pravilov on 2.02.25.
//

#ifndef DYNAMICCAMERA_H
#define DYNAMICCAMERA_H
#include <random>
#include "Entity.h"
#include "Structures.h"

class DynamicCamera
{
public:
  DynamicCamera(Camera2D * p_camera, Entity * p_target);
  ~DynamicCamera();

  Camera2D *getCamera() const;
  void update(float delta);
  void createShake(float p_amplitude, float p_frequency, float p_duration, int priority);
private:
  std::default_random_engine generator;
  Entity * target;
  Camera2D * camera;
  Vector2 shakeVector{};
  float elapsedTime = 0.0f;
  float elapsedTimeFrequency = 0.0f;
  float amplitude = 32.0f;
  float frequency = 0.0f;
  float duration = 0.0f;
  bool isShaking = true;
};

#endif //DYNAMICCAMERA_H
