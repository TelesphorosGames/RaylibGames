#include "raylib.h"


int main()
{

    // Window Dimensions
    int Width = 350;
    int Height{250};
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
        // DrawRectangle(circle_x, circle_y, Width, Height, BLUE);
        // IsKeyDown(KEY_D) &&
        if( circle_x < 330 && circle_x > 20)
        {
        
            if( LastCircleX <= circle_x)
            {
                LastCircleX = circle_x;
                circle_x  += 5;  
                if(circle_x>=320)
                {
                    LastCircleX = circle_x + 2;
                }
            }
            else
            {
                LastCircleX = circle_x;
                circle_x -=5;
                if(circle_x <= 30)
                {
                    LastCircleX = circle_x - 2;
                }
            }
           
        }
    

     if( circle_y < 230 && circle_y > 20)
        {
        
            if( LastCircleY <= circle_y)
            {
                LastCircleY = circle_y;
                circle_y  += 5;  
                if(circle_y>=220)
                {
                    LastCircleY = circle_y + 2;
                }
            }
            else
            {
                LastCircleY = circle_y;
                circle_y -=5;
                if(circle_y <= 30)
                {
                    LastCircleY = circle_y - 2;
                }
            }
           
        }
            
        //     // IsKeyDown(KEY_A) &&
        //   if( circle_x > 30)
        //      {
        //     if(LastCircleX >= circle_x)
        //     {
        //         LastCircleX = circle_x;
        //         circle_x  -= 5; 
        //     }
        //     else
        //     {
        //         LastCircleX = circle_x;
        //         circle_x  += 5; 
        //     }
         
        
    



      
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

