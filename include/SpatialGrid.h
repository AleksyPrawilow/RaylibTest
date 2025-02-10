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

class SpatialGrid
{
public:
  explicit SpatialGrid(EntityManager * p_manager);
  ~SpatialGrid();

  static size_t hashCell(int x, int y);
  size_t getCell(Vector2 position);
  std::vector<int> getNearbyEntities(int collisionLayer, Vector2 position) const;
  void insert(int collisionLayer, int entityId, Vector2 position);
  void remove(int collisionLayer, int entityId, Vector2 position);
  void updateEntity(int collisionLayer, int entityId, Vector2 oldPosition, Vector2 newPosition);
private:
  //Cells are accessed by coordinates key and contain entities near that position
  std::unordered_map<size_t, std::vector<int>> cellMap[10];
  EntityManager * entityManager;
  int cellSize = 48;
};

#endif //SPATIALGRID_H
