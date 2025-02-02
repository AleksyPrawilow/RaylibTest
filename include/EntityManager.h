//
// Created by Alexey Pravilov on 1.02.25.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <iostream>
#include <memory>
#include <ostream>
#include <vector>
#include "Structures.h"
#include "Entity.h"

class Entity;

class EntityManager
{
public:
  EntityManager();
  ~EntityManager();

  template <typename entity> entity * addEntity(structures::EntityData * entityData)
  {
    currentId++;
    std::shared_ptr<entity> newEntity = std::make_shared<entity>(this, entityData);
    newEntity->setId(currentId);
    entitiesMap[currentId] = newEntity;
    entity * newEntityPtr = newEntity.get();
    additionQueue.push_back(newEntity);
    return newEntityPtr;
  }

  int currentId = 0;

  void processNewEntities();
  void processDeletedEntities();
  void unloadTextures();
  bool removeEntity(int id);
  Texture2D * getTexture(const std::string& fileName);
  std::vector<std::shared_ptr<Entity>> * getEntities();

private:
  std::unordered_map<std::string, Texture2D> textures;
  std::unordered_map<int, std::shared_ptr<Entity>> entitiesMap;
  std::vector<std::shared_ptr<Entity>> entities;
  std::vector<std::shared_ptr<Entity>> additionQueue;
  std::vector<int> deletionQueue;
};

#endif //ENTITYMANAGER_H
