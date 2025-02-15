//
// Created by Alexey Pravilov on 6.02.25.
//

#include "../include/Bullet.h"

Bullet::Bullet(EntityManager * p_manager, structures::EntityData * p_data) : Entity(p_manager, p_data)
{
  camera = entityManager->getDynamicCamera();
  glowTexture = *p_manager->getTexture("../res/BulletGlow.png");
  glowSrcRect = Rectangle(0, 0, 6, 6);
  glowDstRect = Rectangle(entityData->position.x, entityData->position.y, 6, 6);
}

void Bullet::setSpeed(float p_speed)
{
  speed = p_speed;
}

void Bullet::setTargetRotation(float p_targetRotation)
{
  targetRotation = p_targetRotation;
  direction = fromAngle(targetRotation);
}

void Bullet::setOffset(float p_offset)
{
  offset = p_offset;
  sinElapsedTime += offset;
}

void Bullet::update(float delta)
{
  setPosition(entityData->position + direction * speed * delta);
}

void Bullet::render(float delta)
{
  if (!isOnScreen())
  {
    return;
  }
  sinElapsedTime += delta;
  float glowScaleModifier = abs(6 * sin(sinElapsedTime * 5));
  glowDstRect.x = entityData->position.x;
  glowDstRect.y = entityData->position.y;
  glowDstRect.width = 6 + glowScaleModifier;
  glowDstRect.height = 6 + glowScaleModifier;
  auto textureOffset = Vector2(3 + glowScaleModifier / 2, 3 + glowScaleModifier / 2);
  DrawTexturePro(glowTexture, glowSrcRect,  glowDstRect, textureOffset, 0.0f, WHITE);
  Entity::render(delta);
}

void Bullet::collidedWithWall(Rectangle &rec)
{
  auto normal = getCollisionNormal(entityData->dstRect, rec);
  direction = Vector2Reflect(direction, normal);
}
