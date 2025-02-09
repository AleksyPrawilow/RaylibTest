//
// Created by Alexey Pravilov on 9.02.25.
//

#ifndef SPATIALGRID_H
#define SPATIALGRID_H
#include <raylib.h>
#include <vector>
#include <unordered_map>
#include "EntityManager.h"

class EntityManager;

class SpatialGrid
{
public:
  explicit SpatialGrid(EntityManager * p_manager);
  ~SpatialGrid();
  //TODO implement collision layers to improve performance
  std::string getCell(Vector2 position) const;
  std::vector<int> getNearbyEntities(Vector2 position) const;
  void insert(int entityId, Vector2 position);
  void remove(int entityId, Vector2 position);
  void updateEntity(int entityId, Vector2 oldPosition, Vector2 newPosition);
private:
  //Cells are accessed by coordinates key and contain entities near that position
  std::unordered_map<std::string, std::vector<int>> cellMap;
  EntityManager * entityManager;
  int cellSize = 48;
};

#endif //SPATIALGRID_H
