//
// Created by Alexey Pravilov on 1.02.25.
//

#include "../include/Entity.h"

Entity::~Entity()
{
  entityManager = nullptr;
  delete entityData;
}

Entity::Entity(EntityManager * p_manager, structures::EntityData * p_data)
{
  entityManager = p_manager;
  entityData = p_data;
}

Entity::Entity()=default;

Texture2D Entity::getTexture() const
{
  return entityData->texture;
}

Rectangle Entity::getSrcRect() const
{
  return entityData->srcRect;
}

Rectangle Entity::getDstRect() const
{
  return entityData->dstRect;
}

Vector2 Entity::getTextureOffset() const
{
  return entityData->textureOrigin;
}

float Entity::getRotation() const
{
  return entityData->rotation;
}

Color Entity::getTint() const
{
  return entityData->tint;
}

Vector2 Entity::getPosition() const
{
  return entityData->position;
}

Vector2 Entity::getCollisionNormal(const Rectangle A, const Rectangle B)
{
  Rectangle overlap = GetCollisionRec(A, B);
  Vector2 normal;

  if (overlap.width < overlap.height) {
    if (A.x < B.x)
    {
      normal = Vector2( -1, 0);
    }
    else
    {
      normal = Vector2( 1, 0);
    }
  }
  else
  {
    if (A.y < B.y)
    {
      normal = Vector2( 0, -1);
    }
    else
    {
      normal = Vector2(0, 1);
    }
  }

  return normal;
}

Vector2 Entity::getDirection(const Vector2 &A, const Vector2 &B)
{
  return B - A;
}

Vector2 Entity::fromAngle(const float angle)
{
  return Vector2(cos(angle), sin(angle));
}

structures::EntityData * Entity::getEntityData() const
{
  return entityData;
}

void Entity::render()
{
  DrawTexturePro(getTexture(), getSrcRect(), getDstRect(), getTextureOffset(), getRotation(), getTint());
}

void Entity::addEntity(structures::EntityData * data) const
{
  (void)entityManager->addEntity<Entity>(data);
}

void Entity::queueFree() const
{
  entityManager->removeEntity(id);
}

void Entity::setId(const int p_id)
{
  id = p_id;
}

int Entity::getId() const
{
  return id;
}

void Entity::moveAndSlide(Vector2 &velocity, float delta) const
{
  Rectangle temp = entityData->dstRect;
  temp.x = entityData->position.x + velocity.x * 75.0f * delta - 4;
  temp.y = entityData->position.y + velocity.y * 75.0f * delta - 6;
  temp.width = 8;
  temp.height = 12;
  for (const auto &collider : *entityManager->getEntities())
  {
    if (!collider->isSolid)
    {
      continue;
    }
    if (CheckCollisionRecs(temp, collider->getDstRect()))
    {
      auto normal = getCollisionNormal(temp, collider->getDstRect());
      velocity = Vector2Reflect(velocity, normal);
      break;
    }
  }
  entityData->position = entityData->position + velocity * 75.0f * delta;
  entityData->dstRect.x = entityData->position.x;
  entityData->dstRect.y = entityData->position.y;
}

void Entity::update(float delta)
{
}
