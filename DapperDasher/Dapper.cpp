#include "raylib.h"

int main()
{
    const int Width = 512;
    const int Height = 380;

    int Velocity = {0};
    int JumpVelocity = {-22};
    const int Gravity = {1};

    bool bIsInAir = false;



    Texture2D ScarfyCharacter = LoadTexture("textures/scarfy.png");
    Rectangle ScarfyBoundsRectangle;
    ScarfyBoundsRectangle.width = ScarfyCharacter.width/6;
    ScarfyBoundsRectangle.height = ScarfyCharacter.height;
    ScarfyBoundsRectangle.x = 0;
    ScarfyBoundsRectangle.y = 0;

    Vector2 ScarfyPosition;
    ScarfyPosition.x = Width/2 - ScarfyBoundsRectangle.width/2;
    ScarfyPosition.y = Height - ScarfyBoundsRectangle.height;

    InitWindow(Width, Height, "Dapper Dasher");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        

       
       
        if(ScarfyPosition.y >= Height - ScarfyBoundsRectangle.height)
        {
            Velocity = 0;
            ScarfyPosition.y = Height - ScarfyBoundsRectangle.height;
            bIsInAir = false;
        }
        else
        {
            Velocity += Gravity;
            bIsInAir = true;
        }

         if( IsKeyDown(KEY_SPACE) && (!bIsInAir))
        {
            Velocity += JumpVelocity;
        }

       


       ScarfyPosition.y += Velocity;

        // else if (posY < Height-RectHeight)
        // {
        //     Velocity = 10;
        // }
        // else
        // {
        //     Velocity = 0;
        // }
        

        EndDrawing();
    }

    UnloadTexture(ScarfyCharacter);
    CloseWindow();

}