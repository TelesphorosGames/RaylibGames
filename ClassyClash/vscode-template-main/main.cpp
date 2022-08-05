#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

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

  Texture2D GoblinIdleTexture = LoadTexture("characters/goblin_idle_spritesheet.png");
  Texture2D GolblinRunTexture = LoadTexture("characters/goblin_run_spritesheet.png");

  Prop Props[2]={
    Prop{{600,300}, RockTexture},
    Prop{{900,800}, LogTexture}
    };

  Character Knight(WindowWidth, WindowHeight);


  Enemy FirstGoblin{Vector2{50,160}, GoblinIdleTexture, GolblinRunTexture};
  Enemy SecondGoblin{Vector2{300,600}, GoblinIdleTexture, GolblinRunTexture};
  Enemy Slime{Vector2{900,800}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")};


 //FirstGoblin.SetTarget(&Knight);

  Enemy* EnemiesArray[]
  {
    &FirstGoblin,
    &SecondGoblin,
    &Slime
  };

  for (Enemy* Enemies : EnemiesArray)
  {
    Enemies->SetTarget(&Knight);
  }

  
  

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

    if(!Knight.GetAlive())
    {
      DrawText("Game Over!", 55, 45, 40, RED);
      EndDrawing();
      continue;
    }
    else
    {

      std::string KnightHealth = "Health: ";
      KnightHealth.append(std::to_string(Knight.GetHealth()), 0, 5);


      DrawText(KnightHealth.c_str(), 55, 45, 40, RED);
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

    for(Enemy* Enemies : EnemiesArray)
    {
      Enemies->Tick(GetFrameTime());
    }
      
    for(Enemy* Enemies : EnemiesArray)
    {
      if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      {
        if(CheckCollisionRecs(Enemies->GetCollisionRec(), Knight.GetWeaponCollisionRectangle()))
        {
          Enemies->SetAlive(false);
        }
      }
    }

    EndDrawing();
  }

  UnloadTexture(LogTexture);
  UnloadTexture(RockTexture);
  UnloadTexture(Knight.Idle);
  UnloadTexture(Knight.Run);  
  UnloadTexture(Knight.Texture);
  UnloadTexture(GoblinIdleTexture);
  UnloadTexture(GolblinRunTexture);
  UnloadTexture(ClashMap);
  CloseWindow();
}