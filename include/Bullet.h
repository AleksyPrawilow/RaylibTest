//
// Created by Alexey Pravilov on 6.02.25.
//

#ifndef BULLET_H
#define BULLET_H
#include "Entity.h"

class Bullet : public Entity
{
protected:
  float offset = 0.0f;
  float speed = 5.0f;
  float targetRotation = 0.0f;
  DynamicCamera * camera{};
  Texture2D glowTexture{};
  Rectangle glowSrcRect{};
  Rectangle glowDstRect{};
public:
  Bullet() : Entity() {};
  Bullet(EntityManager * p_manager, structures::EntityData * p_data);
  void setSpeed(float p_speed);
  void setTargetRotation(float p_targetRotation);
  void setOffset(float p_offset);
  void update(float delta) override;
  void render() override;
};



#endif //BULLET_H
