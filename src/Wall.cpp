//
// Created by Alexey Pravilov on 4.02.25.
//

#include "../include/Wall.h"

void Wall::changeState()
{

}

void Wall::render()
{
  if (isOnScreen())
  {
    Entity::render();
  }
}