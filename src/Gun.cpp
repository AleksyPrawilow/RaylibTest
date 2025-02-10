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
  updateCursor();
  if (isShooting)
  {
    elapsedTime += delta;
    entityData->dstRect.width  = std::lerp(entityData->dstRect.width,  11.0f, 30.0f * delta);
    entityData->dstRect.height = std::lerp(entityData->dstRect.height, 13.0f, 35.0f * delta);

    if (elapsedTime >= 0.1)
    {
      elapsedTime = 0.0f;
      isShooting  = false;
    }
  }
  else
  {
    entityData->dstRect.width  = std::lerp(entityData->dstRect.width,  22.0f, 20.0f * delta);
    entityData->dstRect.height = std::lerp(entityData->dstRect.height, 11.0f, 25.0f * delta);
  }
  targetRotation = structures::angleTo(Vector2(1, 0), Vector2(GetMouseX() - 640, GetMouseY() - 360)) * RAD2DEG;
  entityData->position = Vector2(parent->getEntityData()->dstRect.x, parent->getEntityData()->dstRect.y + 2);
  entityData->dstRect.x = parent->getEntityData()->dstRect.x;
  entityData->dstRect.y = parent->getEntityData()->dstRect.y + 2;
  entityData->srcRect.height = (GetScreenToWorld2D(GetMousePosition(), *camera->getCamera()).x < entityData->position.x) ? -11.0f : 11.0f;
  entityData->rotation = targetRotation;
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    shoot();
  }
}

void Gun::updateCursor() const
{
  entityManager->getCursorOffset() ->x      = 36.0f + 3.0f * sin(GetTime() * 10.0f);
  entityManager->getCursorOffset() ->y      = 36.0f + 3.0f * sin(GetTime() * 10.0f);
  entityManager->getCursorDstRect()->width  = 72.0f + 6.0f * sin(GetTime() * 10.0f);
  entityManager->getCursorDstRect()->height = 72.0f + 6.0f * sin(GetTime() * 10.0f);
  entityManager->getCursorDstRect()->x      = GetMouseX();
  entityManager->getCursorDstRect()->y      = GetMouseY();
  *entityManager->getCursorRotation()       = GetTime() * RAD2DEG;
}

void Gun::shoot()
{
  camera->createShake(10.0f, 0.01f, 0.25f, 23);
  PlaySound(*sound);
  isShooting = true;
  for (int i = 0; i < 7; i++)
  {
    Vector2 direction = Vector2Normalize(getDirection(entityData->position, GetScreenToWorld2D(GetMousePosition(), *camera->getCamera())));
    float angle = Vector2Angle(Vector2(1.0f, 0.0f), direction);
    auto data = new structures::EntityData();
    data->texture = *entityManager->getTexture("../res/Bullet.png");
    data->srcRect = Rectangle(0, 0, 6, 6);
    data->dstRect = Rectangle(entityData->position.x + direction.x * 5.0f, entityData->position.y + direction.y * 5.0f, 6, 6);
    data->textureOrigin = Vector2(3, 3);
    data->position = entityData->position + direction * 5.0f;
    data->rotation = 0.0f;
    data->tint = WHITE;
    data->shouldBeInSpatialGrid = true;
    auto bullet = entityManager->addEntity<Bullet>(data);
    std::uniform_real_distribution<float> dist(-20, 20);
    bullet->collisionLayer = BULLET;
    bullet->setTargetRotation(dist(generator) * DEG2RAD + angle);
    bullet->setOffset(dist(generator));
    bullet->setSpeed(150.0f + dist(generator));
  }
}
