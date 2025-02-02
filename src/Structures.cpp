//
// Created by Alexey Pravilov on 1.02.25.
//

#include "../include/Structures.h"

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
