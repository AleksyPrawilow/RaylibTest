//
// Created by Alexey Pravilov on 1.02.25.
//

#include "../include/Structures.h"
#include <ostream>

float structures::angleTo(const Vector2 &vec1, const Vector2 &vec2)
{
  const float dotProduct = Vector2DotProduct(vec1, vec2);
  const float magnitudes = Vector2Length(vec1) * Vector2Length(vec2);
  if (magnitudes == 0)
  {
    return 0.0f;
  }
  float cosTheta = dotProduct / magnitudes;
  cosTheta = std::fmax(-1.0f, std::fmin(1.0f, cosTheta));
  float angle = std::acos(cosTheta);
  if (const float crossProduct = vec1.x * vec2.y - vec1.y * vec2.x; crossProduct < 0)
  {
    angle = -angle;
  }
  return angle;
}