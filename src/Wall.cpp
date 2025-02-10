//
// Created by Alexey Pravilov on 4.02.25.
//

#include "../include/Wall.h"

void Wall::changeState()
{

}

void Wall::render(float delta)
{
  if (isOnScreen())
  {
    Entity::render(delta);
  }
}

void Wall::update(float delta)
{
  if (!isSolid)
  {
    return;
  }
  for (auto &collider : entityManager->getNearbyEntities(BULLET, getPosition()))
  {
    if (CheckCollisionRecs(getDstRect(), collider->getDstRect()))
    {
      collider->collidedWithWall(entityData->dstRect);
    }
  }
}
