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

