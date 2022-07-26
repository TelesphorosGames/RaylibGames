#include "raylib.h"


int main()
{

    // Window Dimensions
    int Width = 800;
    int Height{650};
    InitWindow(Width, Height, "Screen");

    // Circle coords
    int circle_x = 175;
    int circle_y = 125;

    int LastCircleX = 0;
    int LastCircleY = 0;

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK); 

        DrawCircle(circle_x, circle_y, 30, GREEN);
        DrawRectangle(300, 0, 50, 50, BLUE);
        // 

        if( circle_x < 330 && IsKeyDown(KEY_D))
        {
            circle_x  += 5;  
             
        }            
            
        if(IsKeyDown(KEY_A) && circle_x > 30)
        {
            circle_x  -= 5; 
        }
        
         
        
    



      
       // IsKeyDown(KEY_W) &&
        //   if(  circle_y > 30)
        // {
        //     LastCircleY = circle_y;
        //     circle_y  -= 5; 
        // }
        

        // //IsKeyDown(KEY_S) && 
        //   if(circle_y <  220)
        // {
        //     LastCircleY = circle_y;
        //     circle_y  += 5; 
        // }

        EndDrawing();
    }


}

