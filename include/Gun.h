//
// Created by Alexey Pravilov on 2.02.25.
//

#ifndef GUN_H
#define GUN_H
#include "Entity.h"
#include "Structures.h"

class Gun : public Entity
{
protected:
  Entity * parent{};
  Camera2D * camera{};
  float targetRotation{};
public:
  Gun() : Entity() {};
  Gun(EntityManager * p_manager, structures::EntityData * p_data);

  void setParent(Entity * p_parent);
  void setCamera(Camera2D * p_camera);
  void update(float delta) override;
};



#endif //GUN_H
