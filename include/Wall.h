//
// Created by Alexey Pravilov on 4.02.25.
//

#ifndef WALL_H
#define WALL_H
#include "Entity.h"

class Wall : public Entity
{
private:
  enum STATE
  {
    NORMAL,
    THIRD_TRANSFORMED,
    TWO_THIRDS_TRANSFORMED
  };
  STATE currentState{};
public:
  Wall() : Entity() {};
  Wall(EntityManager * p_manager, structures::EntityData * p_data) : Entity(p_manager, p_data) {};
  void changeState();
  void render() override;
};

#endif //WALL_H
