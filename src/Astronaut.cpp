//
// Created by Alexey Pravilov on 1.02.25.
//

#include "../include/Astronaut.h"

void Astronaut::update(float delta)
{
  DrawText("Astronaut testt", 20, 20, 20, GREEN);
  structures::Vector2f dir = structures::Vector2f(IsKeyDown(KEY_D) - IsKeyDown(KEY_A), IsKeyDown(KEY_S) - IsKeyDown(KEY_W));
  entityData->position = entityData->position + dir * 50.0f * delta;
  entityData->dstRect.x = entityData->position.x;
  entityData->dstRect.y = entityData->position.y;
}
