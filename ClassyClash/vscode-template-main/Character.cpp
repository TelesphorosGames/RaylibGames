#include "Character.h"
#include "raymath.h"

Character::Character(int WinWidth, int WinHeight) :
WindowWidth(WinWidth),
WindowHeight(WinHeight)

{
    Width = Texture.width / MaxFrames;
    Height = Texture.height;

   }

Vector2 Character::GetScreenPosition()
{

    return {static_cast<float>(WindowWidth / 2 - CharacterScale * (0.5f * Width)), 
                      static_cast<float>(WindowHeight / 2 - CharacterScale * (0.5f * Height))};

}

void Character::TakeDamage(float Damage)
{
    Health -= Damage;

    if(Health<=0.f)
    {
        SetAlive(false);
    }
}

void Character::Tick(float DeltaTime)
{

    if(!GetAlive()) return;
    WorldPositionLastFrame = WorldPosition;
    

    if (IsKeyDown(KEY_A))
    {
        Velocity.x -= 1.0;
    }
    if (IsKeyDown(KEY_D))
    {
        Velocity.x += 1.0;
    }
    if (IsKeyDown(KEY_W))
    {
        Velocity.y -= 1.0;
    }
    if (IsKeyDown(KEY_S))
    {
        Velocity.y += 1.0;
    }

    BaseCharacter::Tick(DeltaTime);

    Vector2 Origin{};
    Vector2 Offset{};
    float Rotation{};

    if(RightLeft > 0.f)
    {
        Origin = { 0.f, Weapon.height*CharacterScale};
        Offset = { 35.f, 55.f };
        WeaponCollisionRec = { GetScreenPosition().x + Offset.x + 10.f, GetScreenPosition().y + Offset.y - Weapon.height *CharacterScale, Weapon.width * CharacterScale, Weapon.height * CharacterScale };
        
        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? Rotation = 35.f : Rotation = 0.f;
        
    }
    else
    {
        Origin = {Weapon.width * CharacterScale, Weapon.height*CharacterScale};
        Offset = { 25.f, 55.f };
        WeaponCollisionRec = { GetScreenPosition().x + Offset.x - Weapon.width* CharacterScale, GetScreenPosition().y + Offset.y - Weapon.height *CharacterScale, Weapon.width * CharacterScale, Weapon.height * CharacterScale };
        Rotation = -30.f;

        IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? Rotation = -35.f : Rotation = 0.f;
    
    }

    // Draw sword

    Rectangle Source = { 0.f, 0.f, static_cast<float>(Weapon.width) * RightLeft, static_cast<float>(Weapon.height)};
    Rectangle Dest = { GetScreenPosition().x + Offset.x, GetScreenPosition().y + Offset.y, Weapon.width * CharacterScale, Weapon.height * CharacterScale};

    DrawTexturePro(Weapon, Source, Dest, Origin, Rotation, WHITE);
    
    // DrawRectangleLines(WeaponCollisionRec.x, WeaponCollisionRec.y, WeaponCollisionRec.width, WeaponCollisionRec.height, RED);
}



