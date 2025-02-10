//
// Created by Alexey Pravilov on 1.02.25.
//

#ifndef ENTITY_H
#define ENTITY_H
#include <random>
#include "Structures.h"
#include "EntityManager.h"

class EntityManager;

class Entity
{
protected:
  std::default_random_engine generator;
  EntityManager * entityManager{};
  structures::EntityData * entityData{};
public:
  Entity();
  Entity(EntityManager * p_manager, structures::EntityData * p_data);
  virtual ~Entity();
  void init();
  virtual void ready();
  Texture2D getTexture() const;
  Rectangle getSrcRect() const;
  Rectangle getDstRect() const;
  Vector2 getTextureOffset() const;
  Vector2 getPosition() const;
  static Vector2 getCollisionNormal(Rectangle A, Rectangle B);
  static Vector2 getDirection(const Vector2 &A, const Vector2 &B);
  static Vector2 fromAngle(float angle);
  static Vector2 project(Vector2 &A, Vector2 &B);
  float getRotation() const;
  Color getTint() const;
  structures::EntityData * getEntityData() const;
  virtual void render(float delta);
  bool isOnScreen() const;
  void addEntity(structures::EntityData * data) const;
  void queueFree() const;
  void setId(int p_id);
  void setPosition(Vector2 p_position);
  int getId() const;
  void moveAndSlide(Vector2 &velocity, float scalar);
  virtual void update(float delta);
  virtual void collidedWithWall(Rectangle &rec);

  bool isSolid{false};
  /*The number of collision layers should not exceed 10, if it does,
   don't forget to change the array size in SpatialGrid.h */
  enum COLLISION_LAYERS
  {
    SOLID,
    PLAYER,
    ENEMY,
    BULLET
  };
  COLLISION_LAYERS collisionLayer{SOLID};
private:
  int id{};
};



#endif //ENTITY_H
