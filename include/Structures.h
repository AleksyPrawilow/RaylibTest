//
// Created by Alexey Pravilov on 1.02.25.
//

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <raylib.h>
#include <cmath>

namespace structures
{
  class Vector2f
  {
    public:
      Vector2f();
      Vector2f(float p_x, float p_y);
      Vector2f operator+(const Vector2f &other) const;
      Vector2f operator-(const Vector2f &other) const;
      Vector2f operator*(float scalar) const;
      Vector2f operator/(float scalar) const;
      Vector2f normalized() const;
      bool operator==(const Vector2f &other) const;
      bool operator!=(const Vector2f &other) const;
      Vector2 toRayVector() const;
      float length() const;
      float dot(const Vector2f &other) const;
      float angleTo(const Vector2f &other) const;

      float x{};
      float y{};
  };

  struct EntityData
  {
    Texture2D texture{};
    Rectangle srcRect{};
    Rectangle dstRect{};
    Vector2f textureOrigin;
    Vector2f position;
    float rotation{};
    Color tint{};
  };
}

#endif //STRUCTURES_H
