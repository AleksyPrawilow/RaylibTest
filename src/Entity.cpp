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

structures::EntityData * Entity::getEntityData() const
{
  return entityData;
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

void Entity::update(float delta)
{
}
