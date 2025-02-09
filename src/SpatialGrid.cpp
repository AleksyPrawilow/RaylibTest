//
// Created by Alexey Pravilov on 9.02.25.
//

#include "../include/SpatialGrid.h"

SpatialGrid::SpatialGrid(EntityManager * p_manager)
{
  entityManager = p_manager;
}

SpatialGrid::~SpatialGrid()
{
  cellMap.clear();
}

std::string SpatialGrid::getCell(Vector2 position) const
{
  const int cellX = static_cast<int>(position.x) / cellSize;
  const int cellY = static_cast<int>(position.y) / cellSize;
  return std::to_string(cellX) + "," + std::to_string(cellY);
}

std::vector<int> SpatialGrid::getNearbyEntities(Vector2 position) const
{
  const int cellX = static_cast<int>(position.x) / cellSize;
  const int cellY = static_cast<int>(position.y) / cellSize;
  std::vector<int> result;
  for (int offsetX = -1; offsetX <= 1; offsetX++)
  {
    for (int offsetY = -1; offsetY <= 1; offsetY++)
    {
      std::string key = std::to_string(cellX + offsetX) + "," + std::to_string(cellY + offsetY);
      auto it = cellMap.find(key);
      if (it != cellMap.end())  // Ensure the key exists before accessing it
      {
        result.insert(result.end(), it->second.begin(), it->second.end());
      }
    }
  }
  return result;
}

void SpatialGrid::insert(int entityId, Vector2 position)
{
  cellMap[getCell(position)].push_back(entityId);
}

void SpatialGrid::remove(int entityId, Vector2 position)
{
  const std::string key = getCell(position);
  auto &cell = cellMap[key];
  std::erase(cell, entityId);
}

void SpatialGrid::updateEntity(int entityId, Vector2 oldPosition, Vector2 newPosition)
{
  const std::string oldKey = getCell(oldPosition);
  const std::string newKey = getCell(newPosition);
  if (oldKey != newKey)
  {
    remove(entityId, oldPosition);
    insert(entityId, newPosition);
  }
}
