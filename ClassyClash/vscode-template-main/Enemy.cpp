#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 inPosition, Texture2D in_Idle_Texture, Texture2D in_Run_Texture) 
{

    Idle= (in_Idle_Texture);
    Run = (in_Run_Texture);
    Texture= (in_Idle_Texture);
    WorldPosition =(inPosition);
    Width = Texture.width / MaxFrames ; 
    Height = Texture.height ; 
    Speed = { 3 } ;
}

void Enemy::Tick(float DeltaTime)
{

    /* get ToTarget
    Normalize toTarget
    Multiply ToTarget by Speed
    Move enemy ( set world position)

    */

   Vector2 ToTarget = Vector2Subtract(Target->GetScreenPosition(), ScreenPosition);
   
   WorldPosition = Vector2Add(WorldPosition, Vector2Scale(Vector2Normalize(ToTarget), Speed));



    ScreenPosition = Vector2Subtract(WorldPosition, Target->GetWorldPosition());

    BaseCharacter::Tick(DeltaTime);

    
}
