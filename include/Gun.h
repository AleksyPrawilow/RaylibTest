//
// Created by Alexey Pravilov on 2.02.25.
//

#ifndef GUN_H
#define GUN_H
#include "DynamicCamera.h"
#include "Entity.h"
#include "Structures.h"

class Gun : public Entity
{
protected:
  Entity * parent{};
  DynamicCamera * camera{};
  Sound * sound{};
  float targetRotation{};
  float elapsedTime{};
  bool isShooting = false;
public:
  Gun() : Entity() {};
  Gun(EntityManager * p_manager, structures::EntityData * p_data);

  void setParent(Entity * p_parent);
  void setCamera(DynamicCamera *p_camera);
  void update(float delta) override;
};



#endif //GUN_H
