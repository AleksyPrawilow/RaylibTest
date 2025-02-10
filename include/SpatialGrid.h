//
// Created by Alexey Pravilov on 9.02.25.
//

#ifndef SPATIALGRID_H
#define SPATIALGRID_H
#include <raylib.h>
#include <vector>
#include <unordered_map>
#include "EntityManager.h"
#include "Entity.h"

class EntityManager;
class Entity;

class SpatialGrid
{
public:
  explicit SpatialGrid(EntityManager * p_manager);
  ~SpatialGrid();

  static size_t hashCell(int x, int y);
  size_t getCell(Vector2 position);
  std::vector<Entity *> getNearbyEntities(int collisionLayer, Vector2 position) const;
  void insert(int collisionLayer, Entity * entity, Vector2 position);
  void remove(int collisionLayer, Entity * entity, Vector2 position);
  void updateEntity(int collisionLayer, Entity * entity, Vector2 oldPosition, Vector2 newPosition);
private:
  //Layers are divided into maps of cells, which are accessed by hashed coordinates key and contain pointers to entities near that position
  std::unordered_map<size_t, std::vector<Entity *>> cellMap[10];
  EntityManager * entityManager;
  int cellSize = 48;
};

#endif //SPATIALGRID_H
