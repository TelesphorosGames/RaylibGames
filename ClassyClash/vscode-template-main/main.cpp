#include "raylib.h"
#include "raymath.h"

int main()
{
    const int WindowWidth = 720;
    const int WindowHeight = 480;
    InitWindow(WindowWidth, WindowHeight, "EZ Clash");

    Texture2D ClashMap = LoadTexture("nature_tileset/ClashMap.png");
    Vector2 MapPos = {0,0};
    float MovementSpeed = 3.f;
    Vector2 ScaledMapPos{};


    Texture2D Knight = LoadTexture("characters/knight_idle_spritesheet.png");

    Vector2 KnightPosition =  { (float)WindowWidth/2 - 4 * (0.5f * (float)Knight.width/6), (float)WindowHeight/2 - 4* ( 0.5f  * (float)Knight.height )} ;
   
    // 1 = facing right, -1 = facing left
    float RightLeft = 1.f; 

    float RunningTime{};
    const float UpdateTime{1.f/12.f};
    int Frame{};
    const int maxFrames = 6;

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        Vector2 Direction{};

        if(IsKeyDown(KEY_A))
        {
          Direction.x -= 1.0;
        }
        if(IsKeyDown(KEY_D))
        {
          Direction.x += 1.0;
        }
        if(IsKeyDown(KEY_W))
        {
          Direction.y -= 1.0;
        }
        if(IsKeyDown(KEY_S))
        {
          Direction.y += 1.0;
        }

        if(Vector2Length(Direction) != 0.0)
        {

            MapPos = Vector2Subtract(MapPos,  Vector2Normalize(Direction));
            ScaledMapPos = Vector2Scale(MapPos, MovementSpeed);

            Direction.x > 0.f ? RightLeft = 1.f : RightLeft = -1.f;



        }

        DrawTextureEx(ClashMap, ScaledMapPos, 0.f, 4.0f, WHITE);

        RunningTime += GetFrameTime();

        if(RunningTime >= UpdateTime)
        {
                Frame++;
                RunningTime = 0.f;
                if(Frame>maxFrames)
                {
                    Frame = 0.f;
                }
        }
        Rectangle KnightSource = {(float)Knight.width / 6.f * Frame, 0, (float)Knight.width / 6.f * RightLeft, (float)Knight.height};
        Rectangle KnightDest = {KnightPosition.x , KnightPosition.y, ((float)Knight.width / 6.f) * 4.0f , (float)Knight.height * 4.0f};


        DrawTexturePro(Knight, KnightSource, KnightDest, {0,0}, 0, WHITE);

        EndDrawing();
    }


    UnloadTexture(Knight);
    UnloadTexture(ClashMap);
    CloseWindow();
}