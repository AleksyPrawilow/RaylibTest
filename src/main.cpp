#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "../include/EntityManager.h"
#include "../include/Astronaut.h"
#include "../include/Wall.h"
#include "../include/DynamicCamera.h"

void createLevel(EntityManager * entity_manager);

int main()
{
  ChangeDirectory(GetApplicationDirectory());

  constexpr int screenWidth   = 1280;
  constexpr int screenHeight  = 720;
  constexpr std::string title = "Test Game";

  InitWindow(screenWidth, screenHeight, title.c_str());
  InitAudioDevice();

  auto music          = LoadMusicStream("../res/IcyPath.mp3");
  auto cursorTexture  = LoadTexture("../res/Crosshair.png");
  auto cursorSrcRect  = Rectangle(0, 0, 24, 24);
  auto cursorDstRect  = Rectangle(0, 0, 72, 72);
  auto cursorOffset   = Vector2(36, 36);
  auto cursorRotation = 0.0f;
  auto cursorColor    = WHITE;

  PlayMusicStream(music);
  //SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
  SetExitKey(0);

  auto entityManager = EntityManager();
  entityManager.setCursorDstRect (&cursorDstRect);
  entityManager.setCursorOffset  (&cursorOffset);
  entityManager.setCursorColor   (&cursorColor);
  entityManager.setCursorRotation(&cursorRotation);
  createLevel(&entityManager);

  auto * data         = new structures::EntityData();
  data->texture       = *entityManager.getTexture("../res/Astronaut.png");
  data->srcRect       = Rectangle(0, 0, 12, 12);
  data->dstRect       = Rectangle(150, 150, 12, 12);
  data->position      = Vector2(150, 150);
  data->textureOrigin = Vector2(6, 6);
  data->rotation      = 0.0f;
  data->tint          = WHITE;
  data->shouldBeInSpatialGrid = true;
  
  auto * player        = entityManager.addEntity<Astronaut>(data);
  auto * camera        = new Camera2D();
  auto * dynamicCamera = new DynamicCamera(camera, player);
  entityManager.setDynamicCamera(dynamicCamera);
  camera->target = player->getEntityData()->position;
  camera->zoom = 7.0f;
  player->collisionLayer = Entity::PLAYER;
  player->setCamera(dynamicCamera);

  while (!WindowShouldClose())
  {
    dynamicCamera->update(GetFrameTime());
    UpdateMusicStream(music);
    if (IsKeyPressed(KEY_F1))
    {
      ToggleFullscreen();
    }
    BeginDrawing();
    ClearBackground(YELLOW);
    BeginMode2D(*camera);
    for (const auto &entity : *entityManager.getEntities())
    {
      entity->update(GetFrameTime());
      entity->render();
    }
    EndMode2D();
    DrawFPS(10, 10);
    HideCursor();
    DrawTexturePro(cursorTexture, cursorSrcRect, cursorDstRect, cursorOffset, cursorRotation, cursorColor);
    entityManager.processDeletedEntities();
    entityManager.processNewEntities();
    EndDrawing();
  }
  CloseWindow();

  return 0;
}

void createLevel(EntityManager * entity_manager)
{
  int level[21][21] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  };
  for (int i = 0; i < 21; i++)
  {
    for (int j = 0; j < 21; j++)
    {
      structures::EntityData * data = nullptr;
      Wall * wall = nullptr;
      switch (level[i][j])
      {
        case 1:
          data = new structures::EntityData();
          data->textureOrigin = Vector2(0, 0);
          data->srcRect = Rectangle(0, 0, 24, 24);
          data->dstRect = Rectangle(i * 24, j * 24, 24, 24);
          data->position = Vector2(i * 24, j * 24);
          data->rotation = 0.0f;
          data->tint = WHITE;
          data->shouldBeInSpatialGrid = true;
          data->texture = *entity_manager->getTexture("../res/Wall.png");
          wall = entity_manager->addEntity<Wall>(data);
          wall->isSolid = true;
          wall->collisionLayer = Entity::SOLID;
          break;
        default:
          data = new structures::EntityData();
          data->textureOrigin = Vector2(0, 0);
          data->srcRect = Rectangle(24, 0, 24, 24);
          data->dstRect = Rectangle(i * 24, j * 24, 24, 24);
          data->position = Vector2(i * 24, j * 24);
          data->rotation = 0.0f;
          data->tint = WHITE;
          data->texture = *entity_manager->getTexture("../res/Wall.png");
          wall = entity_manager->addEntity<Wall>(data);
          wall->isSolid = false;
          break;
      }
    }
  }
}
