//
// Created by Alexey Pravilov on 6.02.25.
//

#include "Bullet.h"

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
  Entity::render();
}
