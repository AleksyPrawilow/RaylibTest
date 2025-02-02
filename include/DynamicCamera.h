//
// Created by Alexey Pravilov on 2.02.25.
//

#ifndef DYNAMICCAMERA_H
#define DYNAMICCAMERA_H

#include "Entity.h"
#include "Structures.h"

class DynamicCamera
{
public:
  DynamicCamera(Camera2D * p_camera, Entity * p_target);
  ~DynamicCamera();
  void update();
private:
  Entity * target;
  Camera2D * camera;
};

#endif //DYNAMICCAMERA_H
