//
// Created by Alexey Pravilov on 1.02.25.
//

#include "../include/EntityManager.h"

EntityManager::EntityManager()
{
  grid = new SpatialGrid(this);
}

EntityManager::~EntityManager()=default;

void EntityManager::processNewEntities()
{
  for (auto &entity : additionQueue)
  {
    entity->init();
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

void EntityManager::unloadSounds()
{
  for (const auto &sound : sounds)
  {
    UnloadSound(sound.second);
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

Sound * EntityManager::getSound(const std::string &fileName)
{
  if (fileName.empty())
  {
    return nullptr;
  }
  if (sounds.contains(fileName))
  {
    return &sounds[fileName];
  }
  sounds[fileName] = LoadSound(fileName.c_str());
  return &sounds[fileName];
}

Rectangle * EntityManager::getCursorDstRect() const
{
  return cursorDstRect;
}

Vector2 * EntityManager::getCursorOffset() const
{
  return cursorOffset;
}

Color * EntityManager::getCursorColor() const
{
  return cursorColor;
}

DynamicCamera * EntityManager::getDynamicCamera() const
{
  return camera;
}

Entity * EntityManager::getEntityById(int id)
{
  auto it = entitiesMap.find(id);
  if (it == entitiesMap.end())
  {
    return nullptr;
  }
  return entitiesMap[id].get();
}

void EntityManager::setDynamicCamera(DynamicCamera * p_dynamicCamera)
{
  camera = p_dynamicCamera;
}

float * EntityManager::getCursorRotation() const
{
  return cursorRotation;
}

void EntityManager::initEntityCell(int entityId, Vector2 position) const
{
  grid->insert(entityId, position);
}

void EntityManager::updateEntityCell(int entityId, Vector2 oldPosition, Vector2 newPosition) const
{
  grid->updateEntity(entityId, oldPosition, newPosition);
}

void EntityManager::setCursorDstRect(Rectangle * p_cursorDstRect)
{
  cursorDstRect = p_cursorDstRect;
}

void EntityManager::setCursorOffset(Vector2 * p_cursorOffset)
{
  cursorOffset = p_cursorOffset;
}

void EntityManager::setCursorColor(Color * p_cursorColor)
{
  cursorColor = p_cursorColor;
}

void EntityManager::setCursorRotation(float * p_cursorRotation)
{
  cursorRotation = p_cursorRotation;
}

std::vector<std::shared_ptr<Entity> > *EntityManager::getEntities()
{
  return &entities;
}

std::vector<int> EntityManager::getNearbyEntities(Vector2 position) const
{
  return grid->getNearbyEntities(position);
}
