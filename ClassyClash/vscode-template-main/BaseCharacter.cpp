#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::UndoMovement()
{
    WorldPosition = WorldPositionLastFrame;
}

Rectangle BaseCharacter::GetCollisionRec()
{
     return Rectangle{ 
        GetScreenPosition().x,
        GetScreenPosition().y,
        Width * CharacterScale,
        Height * CharacterScale
    };
}

void BaseCharacter::Tick(float DeltaTime)
{
   
    RunningTime += DeltaTime;

    if (RunningTime >= UpdateTime)
    {
        Frame++;
        RunningTime = 0.f;
        if (Frame > MaxFrames)
        {
            Frame = 0.f;
        }
    }
    Rectangle Source = {Width * Frame, 0, Width * RightLeft, Height};
    Rectangle Dest = {GetScreenPosition().x, GetScreenPosition().y, Width * CharacterScale, Height * CharacterScale};
    DrawTexturePro(Texture, Source, Dest, {0, 0}, 0, WHITE);

    
    if (Vector2Length(Velocity) != 0.0)
    {
        Texture = Run;
        WorldPosition = Vector2Add(WorldPosition, Vector2Scale(Vector2Normalize(Velocity), Speed));

        Velocity.x > 0.f ? RightLeft = 1.f : RightLeft = -1.f;
    }
    else
    {
        Texture = Idle;
    }
    Velocity={};

}
