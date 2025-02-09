//
// Created by Alexey Pravilov on 1.02.25.
//

#include "../include/Entity.h"

Entity::~Entity()
{
  entityManager = nullptr;
  delete entityData;
}

void Entity::init()
{
  if (entityData->shouldBeInSpatialGrid)
  {
    entityManager->initEntityCell(id, entityData->position);
  }
  ready();
}

void Entity::ready()
{
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

Vector2 Entity::project(Vector2 &A, Vector2 &B)
{
  float bSquared = B.x * B.x + B.y * B.y;
  if (bSquared == 0.0f)
  {
    return Vector2(0.0f, 0.0f);
  }
  float scale = Vector2DotProduct(A, B) / bSquared;
  return Vector2(B.x * scale, B.y * scale);
}

structures::EntityData * Entity::getEntityData() const
{
  return entityData;
}

void Entity::render()
{
  DrawTexturePro(getTexture(), getSrcRect(), getDstRect(), getTextureOffset(), getRotation(), getTint());
}

bool Entity::isOnScreen()
{
  Vector2 screenPos = GetWorldToScreen2D(entityData->position, *entityManager->getDynamicCamera()->getCamera());
  if (screenPos.x < -200 || screenPos.x > 1480 || screenPos.y < -200  || screenPos.y > 920)
  {
    return false;
  }
  return true;
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

void Entity::setPosition(const Vector2 &p_position) const
{
  entityManager->updateEntityCell(id, entityData->position, p_position);
  entityData->position = p_position;
  entityData->dstRect.x = entityData->position.x;
  entityData->dstRect.y = entityData->position.y;
}

int Entity::getId() const
{
  return id;
}

void Entity::moveAndSlide(Vector2 &velocity, float scalar) const
{
  Rectangle temp = entityData->dstRect;
  temp.width = 8;
  temp.height = 12;
  temp.x = entityData->position.x + velocity.x * scalar - temp.width / 2;
  temp.y = entityData->position.y + velocity.y * scalar - temp.height / 2;
  for (const auto &colliderId : entityManager->getNearbyEntities(entityData->position))
  {
    Entity * collider = entityManager->getEntityById(colliderId);
    if (!collider->isSolid)
    {
      continue;
    }
    if (CheckCollisionRecs(temp, collider->getDstRect()))
    {
      auto normal = getCollisionNormal(temp, collider->getDstRect());
      Vector2 projection = project(velocity, normal);
      velocity = velocity - projection;
      temp.x = entityData->position.x + velocity.x * scalar - temp.width / 2;
      temp.y = entityData->position.y + velocity.y * scalar - temp.height / 2;
      if (CheckCollisionRecs(temp, collider->getDstRect()))
      {
        velocity = Vector2Zero();
      }
      break;
    }
    collider = nullptr;
  }
  setPosition(entityData->position + velocity * scalar);
}

void Entity::update(float delta)
{
}
