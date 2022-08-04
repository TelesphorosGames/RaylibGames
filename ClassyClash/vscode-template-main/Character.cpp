#include "Character.h"
#include "raymath.h"

Character::Character(int WindowWidth, int WindowHeight)
{
    Width = Texture.width / MaxFrames;
    Height = Texture.height;

    ScreenPosition = {static_cast<float>(WindowWidth / 2 - CharacterScale * (0.5f * Width)), 
                      static_cast<float>(WindowHeight / 2 - CharacterScale * (0.5f * Height))};
}


void Character::Tick(float DeltaTime)
{

    WorldPositionLastFrame = WorldPosition;
    Vector2 Direction{};

    if (IsKeyDown(KEY_A))
    {
        Direction.x -= 1.0;
    }
    if (IsKeyDown(KEY_D))
    {
        Direction.x += 1.0;
    }
    if (IsKeyDown(KEY_W))
    {
        Direction.y -= 1.0;
    }
    if (IsKeyDown(KEY_S))
    {
        Direction.y += 1.0;
    }

    if (Vector2Length(Direction) != 0.0)
    {

        Texture = Run;
        WorldPosition = Vector2Add(WorldPosition, Vector2Scale(Vector2Normalize(Direction), Speed));

        Direction.x > 0.f ? RightLeft = 1.f : RightLeft = -1.f;
    }
    else
    {
        Texture = Idle;
    }

    BaseCharacter::Tick(DeltaTime);
}

