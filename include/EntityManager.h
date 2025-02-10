//
// Created by Alexey Pravilov on 1.02.25.
//

#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H
#include <iostream>
#include <ostream>
#include <vector>
#include "SpatialGrid.h"
#include "DynamicCamera.h"
#include "Structures.h"
#include "Entity.h"

class Entity;
class DynamicCamera;
class SpatialGrid;

class EntityManager
{
public:
  EntityManager();
  ~EntityManager();
  //TODO: Add entity grouping for more efficient collision detection
  template <typename entity> entity * addEntity(structures::EntityData * entityData)
  {
    currentId++;
    std::cout << currentId << std::endl;
    std::shared_ptr<entity> newEntity = std::make_shared<entity>(this, entityData);
    newEntity->setId(currentId);
    entitiesMap[currentId] = newEntity;
    entity * newEntityPtr = newEntity.get();
    additionQueue.push_back(newEntity);
    return newEntityPtr;
  }

  int currentId = 0;

  void            processNewEntities();
  void            processDeletedEntities();
  void            unloadTextures();
  void            unloadSounds();
  bool            removeEntity(int id);
  Texture2D     * getTexture(const std::string &fileName);
  Sound         * getSound(const std::string &fileName);
  Rectangle     * getCursorDstRect() const;
  Vector2       * getCursorOffset() const;
  Color         * getCursorColor() const;
  DynamicCamera * getDynamicCamera() const;
  Entity        * getEntityById(int id);
  float         * getCursorRotation() const;
  void            initEntityCell(int collisionLayer, Entity *entity, Vector2 position) const;
  void            updateEntityCell(int collisionLayer, Entity *entity, Vector2 oldPosition, Vector2 newPosition) const;
  void            setCursorDstRect(Rectangle * p_cursorDstRect);
  void            setCursorOffset(Vector2 * p_cursorOffset);
  void            setCursorColor(Color * p_cursorColor);
  void            setCursorRotation(float * p_cursorRotation);
  void            setDynamicCamera(DynamicCamera * p_dynamicCamera);
  std::vector<std::shared_ptr<Entity>> * getEntities();
  std::vector<Entity *>                  getNearbyEntities(int collisionLayer, Vector2 position) const;

private:
  Rectangle * cursorDstRect {};
  Vector2   * cursorOffset  {};
  Color     * cursorColor   {};
  float     * cursorRotation{};
  DynamicCamera     * camera{};
  SpatialGrid       * grid  {};
  std::unordered_map<std::string, Texture2D>                            textures;
  std::unordered_map<std::string, Sound>                                sounds;
  std::unordered_map<int, std::shared_ptr<Entity>>                      entitiesMap;
  std::unordered_map<std::string, std::vector<std::shared_ptr<Entity>>> groups;
  std::vector<std::shared_ptr<Entity>>                                  entities;
  std::vector<std::shared_ptr<Entity>>                                  additionQueue;
  std::vector<int>                                                      deletionQueue;
};

#endif //ENTITYMANAGER_H
