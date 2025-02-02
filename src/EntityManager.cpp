//
// Created by Alexey Pravilov on 1.02.25.
//

#include "../include/EntityManager.h"

EntityManager::EntityManager()=default;

EntityManager::~EntityManager()=default;

void EntityManager::processNewEntities()
{
  for (auto &entity : additionQueue)
  {
    entities.push_back(std::move(entity));
  }
  additionQueue.clear();
}

void EntityManager::processDeletedEntities()
{
  for (auto &id : deletionQueue)
  {
    auto it = entitiesMap.find(id);
    std::shared_ptr<Entity> entity = it->second;
    entitiesMap.erase(it);
    if (const auto vecIt = std::ranges::find(entities, entity); vecIt != entities.end())
    {
      printf("%lu Deleted\n", entities.size());
      std::swap(*vecIt, entities.back());
      entities.pop_back();
    }
  }
  deletionQueue.clear();
}

void EntityManager::unloadTextures()
{
  for (const auto &texture : textures)
  {
    UnloadTexture(texture.second);
  }
  textures.clear();
}

bool EntityManager::removeEntity(int id)
{
  auto it = entitiesMap.find(id);
  if (it == entitiesMap.end())
  {
    return false;
  }
  deletionQueue.push_back(id);
  return true;
}

Texture2D * EntityManager::getTexture(const std::string &fileName)
{
  if (fileName.empty())
  {
    return nullptr;
  }
  if (textures.contains(fileName))
  {
    return &textures[fileName];
  }
  textures[fileName] = LoadTexture(fileName.c_str());
  return &textures[fileName];
}

std::vector<std::shared_ptr<Entity> > *EntityManager::getEntities()
{
  return &entities;
}
