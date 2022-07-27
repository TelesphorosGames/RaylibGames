#include "raylib.h"

struct AnimationData
{
    // the rectangle associated with the sprite
    Rectangle rec;
    // the position that the rectangle will be drawn on screen at
    Vector2 pos;
    // the current frame's number
    int frame;
    // how often should the animation update
    float updateTime;
    // running time, reset for animation at time of frame update
    float runningTime;
};

int main()
{

    int WindowDimensions[2] = { 1920, 1080 };
    int Width = 1920;
    int Height = 1080;
    InitWindow(WindowDimensions[0], WindowDimensions[1], "Dapper Dasher");
    SetTargetFPS(60);

    int Velocity = {0};

    // pixels / second
    int JumpVelocity = {-600};

    // pixels / second / second
    const int Gravity = {1'000};

    bool bIsInAir = false;


    Texture2D NebulaTexture = LoadTexture("textures/12_nebula_spritesheet.png");

    const int NumberOfNebulae = { 7 };
    
    AnimationData NebulaeArray[NumberOfNebulae] = { };

    for (int i = 0, t = 0; i < NumberOfNebulae; i++, t +=300)
    {
        NebulaeArray[i].rec.x = 0.f;
        NebulaeArray[i].rec.y=0.f;
        NebulaeArray[i].rec.width = NebulaTexture.width/8;
        NebulaeArray[i].rec.height = NebulaTexture.height/8;
        NebulaeArray[i].pos.x = Width + t;
        NebulaeArray[i].pos.y = Height - NebulaTexture.height/8;
        NebulaeArray[i].frame = 0;
        NebulaeArray[i].runningTime = 0.f;
        NebulaeArray[i].updateTime = 0.f;
    }
    
    // in pixles / second 
    int NebulaVelocity = {-300 };

    // Scarfy Character Variables 
    Texture2D Scarfy = LoadTexture("textures/scarfy.png");

    AnimationData ScarfyData;

    ScarfyData.rec.width = Scarfy.width/6;
    ScarfyData.rec.height = Scarfy.height;
    ScarfyData.rec.x = 0;
    ScarfyData.rec.y = 0;

    ScarfyData.pos.x = Width/2 - ScarfyData.rec.width / 2 ;
    ScarfyData.pos.y = Height - ScarfyData.rec.height;

    ScarfyData.frame = 0;
    ScarfyData.updateTime = { 1.0f/12.0f };
    ScarfyData.runningTime = 0.f;


    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        const float DeltaTime = { GetFrameTime() };
        ScarfyData.runningTime += DeltaTime;

        if(ScarfyData.pos.y >= Height - ScarfyData.rec.height)
        {
            Velocity = 0;
            ScarfyData.pos.y = Height - ScarfyData.rec.height;
            bIsInAir = false;
        }
        else
        {
            Velocity += Gravity * DeltaTime;
            bIsInAir = true;
        }

         if( IsKeyDown(KEY_SPACE) && (!bIsInAir))
        {
            Velocity += JumpVelocity;
        }

        
        for (int i = 0; i < NumberOfNebulae; i++)
        {
            // Update Nebula position
            NebulaeArray[i].pos.x += NebulaVelocity * DeltaTime;
        }



        for (int i = 0; i < NumberOfNebulae; i++)
        {

            if (NebulaeArray[i].runningTime >= NebulaeArray[i].updateTime)
            {
                NebulaeArray[i].runningTime = 0;

                NebulaeArray[i].rec.x = NebulaeArray[i].frame * NebulaeArray[i].rec.width;
                NebulaeArray[i].frame++;
                if(NebulaeArray[i].frame > 7)
                {
                    NebulaeArray[i].frame = 0;
                }
            }
        }
        

        
        

        
        // Update Scarfy's jumping position value based on velocity * deltatime
        ScarfyData.pos.y += Velocity * DeltaTime;

        if(ScarfyData.runningTime >= ScarfyData.updateTime)
        {
            ScarfyData.runningTime = 0;

            if(!bIsInAir)
            {
                 ScarfyData.rec.x = ScarfyData.frame * ScarfyData.rec.width;
            
                ScarfyData.frame++;
                if(ScarfyData.frame > 5)
                {
                    ScarfyData.frame = 0;
                } 
            }
           
        }
       
        // Draw Nebulae
        for (int i = 0; i < NumberOfNebulae; i++)
        {
            DrawTextureRec(NebulaTexture, NebulaeArray[i].rec, NebulaeArray[i].pos, WHITE);
        }
        
        
    

        // Draw Scarfy
        DrawTextureRec(Scarfy, ScarfyData.rec, ScarfyData.pos, WHITE);


        EndDrawing();
    }

    UnloadTexture(NebulaTexture);
    UnloadTexture(Scarfy);
    CloseWindow();

}