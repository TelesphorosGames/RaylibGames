#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"


class Enemy : public BaseCharacter
{
    

public:

    Enemy(Vector2 inPosition, Texture2D in_Idle_Texture, Texture2D in_Run_Texture);

    void SetTarget (Character* inTarget) { Target = inTarget ;}

    virtual void Tick(float DeltaTime) override;

    virtual Vector2 GetScreenPosition() override;
private:

    Character* Target;

    float DamagePerSecond;

    float Radius = {25.f};



};