#include "raylib.h"
#include <cstdio>
#include <iostream>


int main()
{

   
    // Window Dimensions
    int Width = 800;
    int Height{650};
    InitWindow(Width, Height, "Screen");



    // Circle coords
    int circle_x = 175;
    int circle_y = 125;
    int circle_radius = 25;

    int l_circle_x = { circle_x - circle_radius };
    int r_circle_x = { circle_x + circle_radius };
    int u_circle_y = { circle_y - circle_radius };
    int b_circle_y = { circle_y + circle_radius };

    int circle_growth = 1;

    // axe

    int axe_x = { 400 };
    int axe_y = {0} ;
    int axe_width = { 50 };
    int axe_height = { 50 };

    int l_axe_x = { axe_x -5 };
    int r_axe_x = { axe_x + axe_width -5 }; 
    int u_axe_y = { axe_y -5 };
    int b_axe_y = { axe_y + axe_height -5 };

    int growth_x = 2;
    int growth_y = 2;

    int direction_x = { 10 };
    int direction_y = { 10 };

    bool collision_with_axe =  {(r_circle_x >= l_axe_x) && (b_axe_y >= u_circle_y) && (u_axe_y <= b_circle_y) && (r_axe_x >= l_circle_x)};

    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK); 

        DrawCircle(circle_x, circle_y, circle_radius, GREEN);
        DrawRectangle(axe_x, axe_y, axe_width, axe_height, BLUE);
    
       

        // Moving the axe, making sure it's direction changes when hitting screen edge

        if(collision_with_axe)
        {
            DrawText("Game Over!! \n ENTER \nto restart.", Width / 2, Height /2 , 45, RED);
            if(IsKeyPressed(KEY_ENTER))
            {
                circle_x = 175;
                circle_y = 125;

                axe_x = 400;
                axe_y = 0;


                collision_with_axe = false;
            }
            
        }
        else
        {

            circle_radius += circle_growth;

            if(circle_radius > 50 || circle_radius < 6)
            {
                circle_growth = -circle_growth;
            }

            axe_height += growth_y;
            axe_width += growth_x;

            if(axe_height > 250 || axe_height < 15)
            {
                growth_y = -growth_y;
            }
    
            if(axe_width > 250 || axe_width < 15)
            {
                growth_x = -growth_x;
            }

            // update edges for collision

            l_circle_x = { circle_x - circle_radius }; 
            r_circle_x = { circle_x + circle_radius };
            u_circle_y = { circle_y - circle_radius };
            b_circle_y = { circle_y + circle_radius };

            
            l_axe_x = { axe_x };
            r_axe_x = { axe_x + axe_width }; 
            u_axe_y = { axe_y };
            b_axe_y = { axe_y + axe_height };

         

            collision_with_axe =  {(r_circle_x >= l_axe_x) && (b_axe_y >= u_circle_y) && (u_axe_y <= b_circle_y) && (r_axe_x >= l_circle_x)};


            axe_y += direction_y; 
            axe_x += direction_x;


            if(axe_y >  Height || axe_y < 0)
            {
                direction_y = -direction_y;
            }
                if(axe_x >  Width || axe_x < 0)
            {
                direction_x = -direction_x;
            }

            if(IsKeyDown(KEY_D) && circle_x < Width )
            {
                circle_x  += 5;  
                
            }            
                
            if(IsKeyDown(KEY_A) && circle_x > 25)
            {
                circle_x  -= 5; 
            }
      
            if( IsKeyDown(KEY_W)  && (  circle_y > 0 + circle_radius) )
                {
                    circle_y  -= 5; 
                }
                

                if( IsKeyDown(KEY_S) && (circle_y <  Width - circle_radius) )
                {
                    circle_y  += 5; 
                }
        
        }
        EndDrawing();
    }


}

