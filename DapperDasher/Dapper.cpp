#include "raylib.h"

int main()
{
    const int Width = 512;
    const int Height = 380;
    InitWindow(Width, Height, "Dapper Dasher");
    SetTargetFPS(60);


    
    int Velocity = {0};
    int JumpVelocity = {-22};
    const int Gravity = {1};

    bool bIsInAir = false;

    Texture2D Scarfy;
    
    Scarfy = LoadTexture("textures/scarfy.png");

    Rectangle ScarfyBoundsRectangle;
    ScarfyBoundsRectangle.width = Scarfy.width/6;
    ScarfyBoundsRectangle.height = Scarfy.height;
    ScarfyBoundsRectangle.x = 0;
    ScarfyBoundsRectangle.y = 0;

    Vector2 ScarfyPosition;
    ScarfyPosition.x = Width/2 - ScarfyBoundsRectangle.width/2;
    ScarfyPosition.y = Height - ScarfyBoundsRectangle.height;

    

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

       DrawTextureRec(Scarfy, ScarfyBoundsRectangle, ScarfyPosition, WHITE);

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

    
    UnloadTexture(Scarfy);
    CloseWindow();

}