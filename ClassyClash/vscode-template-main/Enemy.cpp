#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 inPosition, Texture2D in_Idle_Texture, Texture2D in_Run_Texture) 
{
    DamagePerSecond={40.f};
    Idle= (in_Idle_Texture);
    Run = (in_Run_Texture);
    Texture= (in_Idle_Texture);
    WorldPosition =(inPosition);
    Width = Texture.width / MaxFrames ; 
    Height = Texture.height ; 
    Speed = { 3 } ;
}

Vector2 Enemy::GetScreenPosition()
{
    return Vector2Subtract(WorldPosition, Target->GetWorldPosition());

}

void Enemy::Tick(float DeltaTime)
{
        if(!GetAlive()) return;
    /* get ToTarget
    Normalize toTarget vector (velocity)
    Multiply ToTarget by Speed
    Move enemy ( set world position)

    */

   Velocity = Vector2Subtract(Target->GetScreenPosition(), GetScreenPosition());
   
    if(Vector2Length(Velocity) <= Radius)
    {
        Velocity = {};
    }

    BaseCharacter::Tick(DeltaTime);

    if(CheckCollisionRecs(Target->GetCollisionRec(), GetCollisionRec()))
    {
        Target->TakeDamage(DamagePerSecond*DeltaTime);
        if(Target->GetHealth()<=0.f)
        {
            Target->SetAlive(false);
        }
    }
    
}
