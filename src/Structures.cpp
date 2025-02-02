//
// Created by Alexey Pravilov on 1.02.25.
//

#include "../include/Structures.h"

#include <iostream>
#include <ostream>

structures::Vector2f::Vector2f()=default;

structures::Vector2f::Vector2f(const float p_x, const float p_y)
{
  x = p_x;
  y = p_y;
}

structures::Vector2f structures::Vector2f::operator+(const Vector2f &other) const
{
  return {x + other.x, y + other.y};
}

structures::Vector2f structures::Vector2f::operator-(const Vector2f &other) const
{
  return {x - other.x, y - other.y};
}

structures::Vector2f structures::Vector2f::operator*(const float scalar) const
{
  return {x * scalar, y * scalar};
}

structures::Vector2f structures::Vector2f::operator/(const float scalar) const
{
  return {x / scalar, y / scalar};
}

structures::Vector2f structures::Vector2f::normalized() const
{
  if (x == 0.0f && y == 0.0f)
  {
    return {x, y};
  }
  const float magnitude = sqrt(x * x + y * y);
  return {x / magnitude, y / magnitude};
}

bool structures::Vector2f::operator==(const Vector2f &other) const
{
  return x == other.x && y == other.y;
}

bool structures::Vector2f::operator!=(const Vector2f &other) const
{
  return x != other.x || y != other.y;
}

Vector2 structures::Vector2f::toRayVector() const
{
  return Vector2(x, y);
}

float structures::Vector2f::length() const
{
  return sqrt(x * x + y * y);
}

float structures::Vector2f::dot(const Vector2f &other) const
{
  return x * other.x + y * other.y;
}

float structures::Vector2f::angleTo(const Vector2f &other) const
{
  const float dotProduct = dot(other);
  const float magnitudes = length() * other.length();
  if (magnitudes == 0)
  {
    return 0.0f;
  }
  float cosTheta = dotProduct / magnitudes;
  cosTheta = std::fmax(-1.0f, std::fmin(1.0f, cosTheta));
  float angle = std::acos(cosTheta);
  if (const float crossProduct = x * other.y - y * other.x; crossProduct < 0)
  {
    angle = -angle;
  }
  return angle;
}