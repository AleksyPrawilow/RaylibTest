//
// Created by Alexey Pravilov on 6.02.25.
//

#include "../include/Bullet.h"

Bullet::Bullet(EntityManager * p_manager, structures::EntityData * p_data) : Entity(p_manager, p_data)
{
  camera = entityManager->getDynamicCamera();
}

void Bullet::setSpeed(float p_speed)
{
  speed = p_speed;
}

void Bullet::setTargetRotation(float p_targetRotation)
{
  targetRotation = p_targetRotation;
}

void Bullet::setOffset(float p_offset)
{
  offset = p_offset;
}

void Bullet::update(float delta)
{
  entityData->position += fromAngle(targetRotation) * speed * delta;
  entityData->dstRect.x = entityData->position.x;
  entityData->dstRect.y = entityData->position.y;
}

void Bullet::render()
{
  Vector2 screenPos = GetWorldToScreen2D(entityData->position, *camera->getCamera());
  if (screenPos.x < -64 || screenPos.x > 1400 || screenPos.y < -64  || screenPos.y > 784)
  {
    return;
  }
  DrawTexturePro(*entityManager->getTexture("../res/BulletGlow.png"), Rectangle(0, 0, 6, 6), Rectangle(entityData->position.x, entityData->position.y, 6 + abs(6 * sin((GetTime() + offset) * 5)), 6 + abs(6 * cos((GetTime() + offset) * 5))), Vector2(3 + abs(3 * sin((GetTime() + offset) * 5)), 3 + abs(3 * cos((GetTime() + offset) * 5))), 0.0f, WHITE);
  //DrawCircle(entityData->position.x, entityData->position.y, 5 + 2 * sin(GetTime() * 10), Color(0, 255, 0, 45));
  Entity::render();
}
