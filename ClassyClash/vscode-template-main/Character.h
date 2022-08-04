#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(int WindowWidth, int WindowHeight);

   

    virtual void Tick(float DeltaTime) override;

    Vector2 GetScreenPosition() { return ScreenPosition ; }

private:

  
};

#endif
