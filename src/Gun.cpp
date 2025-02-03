//
// Created by Alexey Pravilov on 2.02.25.
//

#include "../include/Gun.h"
#include <iostream>

Gun::Gun(EntityManager * p_manager, structures::EntityData * p_data) : Entity(p_manager, p_data)
{
  sound = p_manager->getSound("../res/Pew.wav");
}

void Gun::setParent(Entity * p_parent)
{
  parent = p_parent;
}

void Gun::setCamera(DynamicCamera * p_camera)
{
  camera = p_camera;
}

void Gun::update(float delta)
{
  if (isShooting)
  {
    elapsedTime += delta;
    entityData->dstRect.width = std::lerp(entityData->dstRect.width, 11.0f, 30.0f * delta);
    entityData->dstRect.height = std::lerp(entityData->dstRect.height, 13.0f, 35.0f * delta);

    if (elapsedTime >= 0.1)
    {
      elapsedTime = 0.0f;
      isShooting = false;
    }
  }
  else
  {
    entityData->dstRect.width = std::lerp(entityData->dstRect.width, 22.0f, 20.0f * delta);
    entityData->dstRect.height = std::lerp(entityData->dstRect.height, 11.0f, 25.0f * delta);
  }
  targetRotation = structures::Vector2f(1, 0).angleTo(structures::Vector2f(GetMouseX() - 640, GetMouseY() - 360)) * RAD2DEG;
  entityData->position = structures::Vector2f(parent->getEntityData()->dstRect.x, parent->getEntityData()->dstRect.y + 2);
  entityData->dstRect.x = parent->getEntityData()->dstRect.x;
  entityData->dstRect.y = parent->getEntityData()->dstRect.y + 2;
  entityData->srcRect.height = (GetScreenToWorld2D(GetMousePosition(), *camera->getCamera()).x < entityData->position.x) ? -11.0f : 11.0f;
  entityData->rotation = targetRotation;
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    camera->createShake(10.0f, 0.01f, 0.25f, 23);
    PlaySound(*sound);
    isShooting = true;
  }
}