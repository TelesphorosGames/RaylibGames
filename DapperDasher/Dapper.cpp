#include "raylib.h"

int main()
{
    const int Width = 512;
    const int Height = 380;

    const int RectWidth = {40};
    const int RectHeight = {65};

    int posY = { Height - RectHeight} ;  
    int Velocity = {0};
    int JumpVelocity = {-22};
    const int Gravity = {1};

    bool bIsInAir = false;

    InitWindow(Width, Height, "Dapper Dasher");
    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        

        DrawRectangle(Width/2, posY, RectWidth, RectHeight, GREEN   );



       
        if (posY >= Height-RectHeight)
        {
            Velocity = 0;
            posY = Height - RectHeight;
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

       


        posY  += Velocity;

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

    CloseWindow();

}