//
// Created by Alexey Pravilov on 1.02.25.
//

#ifndef ASTRONAUT_H
#define ASTRONAUT_H
#include "DynamicCamera.h"
#include "Entity.h"
#include "../include/Gun.h"

class Astronaut : public Entity
{
public:
  Astronaut() : Entity() {};
  Astronaut(EntityManager * p_manager, structures::EntityData * p_data) : Entity(p_manager, p_data) {};
  void update(float delta) override;
  void setCamera(DynamicCamera *p_camera);
  void animate();
private:
  DynamicCamera * camera {};
  enum ANIMATION_STATE { IDLE , RUNNING , DEAD };
  ANIMATION_STATE animationState {};
  structures::Vector2f velocity {};
  float animationSpeed = 10.0f;
  float currentTick {};
  float targetRotation {};
};

#endif //ASTRONAUT_H
