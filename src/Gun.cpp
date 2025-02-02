//
// Created by Alexey Pravilov on 2.02.25.
//

#include "../include/Gun.h"

#include <iostream>

Gun::Gun(EntityManager * p_manager, structures::EntityData * p_data) : Entity(p_manager, p_data){}

void Gun::setParent(Entity * p_parent)
{
  parent = p_parent;
}

void Gun::setCamera(Camera2D * p_camera)
{
  camera = p_camera;
}

void Gun::update(float delta)
{
  targetRotation = structures::Vector2f(1, 0).angleTo(structures::Vector2f(GetMouseX() - 640, GetMouseY() - 360)) * RAD2DEG;
  entityData->position = structures::Vector2f(parent->getEntityData()->dstRect.x, parent->getEntityData()->dstRect.y + 2);
  entityData->dstRect.x = parent->getEntityData()->dstRect.x;
  entityData->dstRect.y = parent->getEntityData()->dstRect.y + 2;
  entityData->srcRect.height = (GetScreenToWorld2D(GetMousePosition(), *camera).x < entityData->position.x) ? -11.0f : 11.0f;
  entityData->rotation = targetRotation;
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    std::cout << "PEW\n";
  }
}