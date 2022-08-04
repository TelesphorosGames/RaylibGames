#include "BaseCharacter.h"

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
        ScreenPosition.x,
        ScreenPosition.y,
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
    Rectangle Dest = {ScreenPosition.x, ScreenPosition.y, Width * CharacterScale, Height * CharacterScale};
    DrawTexturePro(Texture, Source, Dest, {0, 0}, 0, WHITE);
}
