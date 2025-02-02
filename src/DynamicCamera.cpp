//
// Created by Alexey Pravilov on 2.02.25.
//

#include "../include/DynamicCamera.h"

DynamicCamera::DynamicCamera(Camera2D * p_camera, Entity * p_target)
{
  camera = p_camera;
  target = p_target;
}

DynamicCamera::~DynamicCamera()=default;

void DynamicCamera::update()
{
  camera->target = target->getEntityData()->position.toRayVector();
  camera->offset = Vector2(1280 -(GetMousePosition().x + 1280 / 2) / 2, 720 -(GetMousePosition().y + 720 / 2) / 2);
}
