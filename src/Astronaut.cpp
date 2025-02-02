//
// Created by Alexey Pravilov on 1.02.25.
//

#include "../include/Astronaut.h"

#include <iostream>

void Astronaut::update(float delta)
{
  std::cout << animationSpeed << std::endl;
  DrawText("hello world", 10, 10, 10, WHITE);
  currentTick += delta;
  if (currentTick > 1.0f / animationSpeed)
  {
    animate();
    currentTick = 0;
  }
  auto dir = structures::Vector2f(IsKeyDown(KEY_D) - IsKeyDown(KEY_A), IsKeyDown(KEY_S) - IsKeyDown(KEY_W)).normalized();
  velocity = velocity + (dir - velocity) / 4.0f;
  targetRotation = velocity.x * 10;
  animationState = (dir.length() > 0.0f) ? RUNNING : IDLE;
  entityData->rotation = targetRotation;
  entityData->position = entityData->position + velocity * 75.0f * delta;
  entityData->dstRect.x = entityData->position.x;
  entityData->dstRect.y = entityData->position.y;
  entityData->srcRect.width = (GetScreenToWorld2D(GetMousePosition(), *camera).x < entityData->position.x) ? 12 : -12;
}

void Astronaut::animate()
{
  switch (animationState)
  {
    case IDLE:
      animationSpeed = 10.0f;
      entityData->srcRect.x += 12;
      if (entityData->srcRect.x > 36)
      {
        entityData->srcRect.x = 0;
      }
      break;
    case RUNNING:
      animationSpeed = 12.0f;
      entityData->srcRect.x += 12;
      if (entityData->srcRect.x > 132)
      {
        entityData->srcRect.x = 48;
      }
      else if (entityData->srcRect.x < 48)
      {
        entityData->srcRect.x = 48;
      }
      break;
    case DEAD:
      animationSpeed = 1;
      break;
  }
}

void Astronaut::setCamera(Camera2D * p_camera)
{
  camera = p_camera;
}
