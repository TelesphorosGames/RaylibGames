#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
  const int WindowWidth = 720;
  const int WindowHeight = 480;
  InitWindow(WindowWidth, WindowHeight, "EZ Clash");

  Texture2D ClashMap = LoadTexture("nature_tileset/ClashMap.png");
  Vector2 MapPos={};
  const float MapScale = {4.0f};

  Character Knight(WindowWidth, WindowHeight);

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);

    MapPos = Vector2Scale(Knight.GetWorldPosition(), -1.f);

    DrawTextureEx(ClashMap, MapPos, 0.f, MapScale, WHITE);
    
    Knight.Tick(GetFrameTime());
    if (Knight.GetWorldPosition().x < 0.f ||
        Knight.GetWorldPosition().y < 0.f ||
        Knight.GetWorldPosition().x + WindowWidth > ClashMap.width * MapScale ||
        Knight.GetWorldPosition().y + WindowHeight > ClashMap.height * MapScale)
    {
      Knight.UndoMovement();
    }

    EndDrawing();
  }

  UnloadTexture(Knight.Idle);
  UnloadTexture(Knight.Run);
  UnloadTexture(Knight.Texture);
  UnloadTexture(ClashMap);
  CloseWindow();
}