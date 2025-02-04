//
// Created by Alexey Pravilov on 1.02.25.
//

#ifndef ENTITY_H
#define ENTITY_H
#include "Structures.h"
#include "EntityManager.h"

class EntityManager;

class Entity
{
protected:
  EntityManager * entityManager{};
  structures::EntityData * entityData{};
public:
  Entity();
  Entity(EntityManager * p_manager, structures::EntityData * p_data);
  virtual ~Entity();
  Texture2D getTexture() const;
  Rectangle getSrcRect() const;
  Rectangle getDstRect() const;
  Vector2 getTextureOffset() const;
  Vector2 getPosition() const;
  float getRotation() const;
  Color getTint() const;
  structures::EntityData * getEntityData() const;
  void addEntity(structures::EntityData * data) const;
  void queueFree() const;
  void setId(int p_id);
  int getId() const;
  virtual void update(float delta);

  bool shouldCollide{false};
private:
  int id{};
};



#endif //ENTITY_H
