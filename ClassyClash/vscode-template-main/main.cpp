#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
  const int WindowWidth = 720;
  const int WindowHeight = 480;
  InitWindow(WindowWidth, WindowHeight, "EZ Clash");

  Texture2D ClashMap = LoadTexture("nature_tileset/ClashMap.png");
  Vector2 MapPos={};
  const float MapScale = {4.0f};

  Texture2D RockTexture = LoadTexture("nature_tileset/Rock.png");
  Texture2D LogTexture = LoadTexture("nature_tileset/Log.png");

  Prop Props[2]={
    Prop{{600,300}, RockTexture},
    Prop{{900,800}, LogTexture}
    };

  Character Knight(WindowWidth, WindowHeight);

  SetTargetFPS(60);
  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(BLACK);

    MapPos = Vector2Scale(Knight.GetWorldPosition(), -1.f);

    DrawTextureEx(ClashMap, MapPos, 0.f, MapScale, WHITE);

    for (Prop allProps : Props)
    {
      allProps.Render(Knight.GetWorldPosition());
    }
    
    Knight.Tick(GetFrameTime());

    if (Knight.GetWorldPosition().x < 0.f ||
        Knight.GetWorldPosition().y < 0.f ||
        Knight.GetWorldPosition().x + WindowWidth > ClashMap.width * MapScale ||
        Knight.GetWorldPosition().y + WindowHeight > ClashMap.height * MapScale)
    {
      Knight.UndoMovement();
    }

    for (Prop allProps : Props)
    {
      bool bCollidedWithProp = CheckCollisionRecs(allProps.GetCollisionRec(Knight.GetWorldPosition()), Knight.GetCollisionRec());
      if(bCollidedWithProp)
      {
        Knight.UndoMovement();
      }
    }


    EndDrawing();
  }

  UnloadTexture(LogTexture);
  UnloadTexture(RockTexture);
  UnloadTexture(Knight.Idle);
  UnloadTexture(Knight.Run);
  UnloadTexture(Knight.Texture);
  UnloadTexture(ClashMap);
  CloseWindow();
}