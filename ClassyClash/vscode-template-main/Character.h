#include "raylib.h"

class Character
{
public:
    Character(int WindowWidth, int WindowHeight);

    Vector2 GetWorldPosition() { return WorldPosition; }

    void Tick(float DeltaTime);
    Texture2D Idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D Run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D Texture = Idle;

    void UndoMovement();

    Rectangle GetCollisionRec();

private:
    float Width{};
    float Height{};

    Vector2 ScreenPosition{};
    Vector2 WorldPosition{};

    Vector2 WorldPositionLastFrame{};

    // 1 = facing right, -1 = facing left
    float RightLeft = 1.f;

    float RunningTime{};
    float UpdateTime{1.f / 12.f};
    int Frame{};
    int maxFrames = 6;
    float CharacterScale={4.0f};
    float Speed = {4.f};
};
