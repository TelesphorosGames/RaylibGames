#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:

    Character(int WindowWidth, int WindowHeight);




    virtual void Tick(float DeltaTime) override;

    virtual Vector2 GetScreenPosition() override;

    Rectangle GetWeaponCollisionRectangle() const { return WeaponCollisionRec ;}

    float GetHealth() const { return Health ;}

    void TakeDamage(float Damage);


private:

    int WindowWidth{};
    int WindowHeight{};

    Texture2D Weapon { LoadTexture("characters/weapon_sword.png")};

    Rectangle WeaponCollisionRec{};

    float Health = {100.f}; 

};

#endif
