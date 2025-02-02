#include <iostream>
#include <raylib.h>
#include "../include/EntityManager.h"
#include "../include/Astronaut.h"
#include "../include/DynamicCamera.h"

int main()
{
  constexpr int screenWidth = 1280;
  constexpr int screenHeight = 720;
  constexpr std::string title = "Test Game";

  InitWindow(screenWidth, screenHeight, title.c_str());
  SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
  SetExitKey(0);

  auto entityManager = EntityManager();
  auto * data = new structures::EntityData();
  data->texture = *entityManager.getTexture("res/Astronaut.png");
  data->srcRect = Rectangle(0, 0, 12, 12);
  data->dstRect = Rectangle(0, 0, 12, 12);
  data->position = structures::Vector2f(0, 0);
  data->textureOrigin = structures::Vector2f(6, 6);
  data->rotation = 0.0f;
  data->tint = WHITE;
  auto * player = entityManager.addEntity<Astronaut>(data);

  auto * camera = new Camera2D();
  auto * dynamicCamera = new DynamicCamera(camera, player);
  camera->target = player->getEntityData()->position.toRayVector();
  camera->zoom = 10.0f;

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(YELLOW);
    dynamicCamera->update();
    BeginMode2D(*camera);
    for (const auto &entity : *entityManager.getEntities())
    {
      DrawTexturePro(entity->getTexture(), entity->getSrcRect(), entity->getDstRect(), entity->getTextureOffset(), entity->getRotation(), entity->getTint());
      entity->update(GetFrameTime());
    }
    EndMode2D();
    entityManager.processDeletedEntities();
    entityManager.processNewEntities();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
