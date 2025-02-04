//
// Created by Alexey Pravilov on 1.02.25.
//

#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <raylib.h>
#include <raymath.h>
#include <cmath>

namespace structures
{
  struct EntityData
  {
    Texture2D texture{};
    Rectangle srcRect{};
    Rectangle dstRect{};
    Vector2 textureOrigin{};
    Vector2 position{};
    float rotation{};
    Color tint{};
  };

  float angleTo(const Vector2 &vec1, const Vector2 &vec2);
}

#endif //STRUCTURES_H
