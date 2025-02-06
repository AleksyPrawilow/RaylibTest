//
// Created by Alexey Pravilov on 1.02.25.
//

#include "../include/Astronaut.h"

#include <iostream>

void Astronaut::update(float delta)
{
  DrawText("hello world", 10, 10, 10, WHITE);
  currentTick += delta;
  if (currentTick > 1.0f / animationSpeed)
  {
    animate();
    currentTick = 0;
  }
  if (animationState == RUNNING)
  {
    entityData->dstRect.height = std::lerp(entityData->dstRect.height, 12.0f + sin(GetTime() * 20.0f) * 2.5f, 7.5f * delta);
    entityData->dstRect.width = std::lerp(entityData->dstRect.width, 12.0f + cos(GetTime() * 20.0f) * 2.0f, 7.5f * delta);
  }
  else
  {
    entityData->dstRect.height = std::lerp(entityData->dstRect.height, 12.0f, 7.5f * delta);
    entityData->dstRect.width = std::lerp(entityData->dstRect.width, 12.0f, 7.5f * delta);
  }
  auto dir = Vector2Normalize(Vector2(IsKeyDown(KEY_D) - IsKeyDown(KEY_A), IsKeyDown(KEY_S) - IsKeyDown(KEY_W)));
  velocity = velocity + (dir - velocity) * 12.0f * delta;
  targetRotation = velocity.x * 10;
  animationState = (Vector2Length(dir) > 0.0f) ? RUNNING : IDLE;
  entityData->rotation = targetRotation;
  moveAndSlide(velocity, delta);
  entityData->srcRect.width = (GetScreenToWorld2D(GetMousePosition(), *camera->getCamera()).x < entityData->position.x) ? 12 : -12;

  if (IsKeyPressed(KEY_UP))
  {
    auto data = new structures::EntityData();
    data->srcRect = Rectangle(0, 0, -22, 11);
    data->dstRect = Rectangle(entityData->position.x + 4, entityData->position.y + 2, 22, 11);
    data->texture = *entityManager->getTexture("../res/ShotgunToxic.png");
    data->rotation = 0.0f;
    data->position = entityData->position;
    data->tint = WHITE;
    data->textureOrigin = Vector2(5.0f, 5.5f);
    auto * gun = entityManager->addEntity<Gun>(data);
    gun->setCamera(camera);
    gun->setParent(this);
  }
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

void Astronaut::setCamera(DynamicCamera * p_camera)
{
  camera = p_camera;
}
