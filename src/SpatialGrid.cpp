//
// Created by Alexey Pravilov on 9.02.25.
//

#include "../include/SpatialGrid.h"

SpatialGrid::SpatialGrid(EntityManager * p_manager)
{
  entityManager = p_manager;
}

SpatialGrid::~SpatialGrid()=default;

size_t SpatialGrid::hashCell(int x, int y)
{
  return (static_cast<size_t>(x) * 73856093) ^ (static_cast<size_t>(y) * 19349663);
}

size_t SpatialGrid::getCell(Vector2 position)
{
  const int cellX = static_cast<int>(position.x) / cellSize;
  const int cellY = static_cast<int>(position.y) / cellSize;
  return hashCell(cellX, cellY);
}

std::vector<int> SpatialGrid::getNearbyEntities(int collisionLayer, Vector2 position) const
{
  const int cellX = static_cast<int>(position.x) / cellSize;
  const int cellY = static_cast<int>(position.y) / cellSize;
  std::vector<int> result;
  result.reserve(32);  //Preallocate memory to reduce resizing. Don't know if it helps though, we did it in class one time and it kinda worked.
  auto &layerMap = cellMap[collisionLayer];

  for (int offsetX = -1; offsetX <= 1; offsetX++)
  {
    for (int offsetY = -1; offsetY <= 1; offsetY++)
    {
      size_t key = hashCell(cellX + offsetX, cellY + offsetY);
      auto it = layerMap.find(key);
      if (it != layerMap.end())
      {
        result.insert(result.end(), it->second.begin(), it->second.end());
      }
    }
  }
  return result;
}

void SpatialGrid::insert(int collisionLayer, int entityId, Vector2 position)
{
  cellMap[collisionLayer][getCell(position)].push_back(entityId);
}

void SpatialGrid::remove(int collisionLayer, int entityId, Vector2 position)
{
  size_t key = getCell(position);
  auto &cell = cellMap[collisionLayer][key];
  cell.erase(std::remove(cell.begin(), cell.end(), entityId), cell.end());
}

void SpatialGrid::updateEntity(int collisionLayer, int entityId, Vector2 oldPosition, Vector2 newPosition)
{
  const size_t oldKey = getCell(oldPosition);
  const size_t newKey = getCell(newPosition);
  if (oldKey != newKey)
  {
    remove(collisionLayer, entityId, oldPosition);
    insert(collisionLayer, entityId, newPosition);
  }
}
