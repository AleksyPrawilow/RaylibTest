//
// Created by Alexey Pravilov on 1.02.25.
//

#ifndef ASTRONAUT_H
#define ASTRONAUT_H
#include "Entity.h"

class Astronaut : public Entity
{
public:
  Astronaut() : Entity() {};
  Astronaut(EntityManager * p_manager, structures::EntityData * p_data) : Entity(p_manager, p_data) {};
  void update(float delta) override;
};



#endif //ASTRONAUT_H
