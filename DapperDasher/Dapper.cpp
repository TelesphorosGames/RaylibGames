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

bool bScarfyOnGround(AnimationData Data, int WindowHeight)
{
   return (Data.pos.y >= WindowHeight - Data.rec.height);
}

AnimationData updateAnimData(AnimationData Data, float DeltaTime, int maxFrames)
{
    Data.runningTime += DeltaTime;
    if(Data.runningTime >= Data.updateTime)
    {
        Data.runningTime = 0.0;
        Data.rec.x = Data.frame * Data.rec.width;
        Data.frame++;
        if (Data.frame > (maxFrames))
        {
           Data.frame = 0; 
        }
    }
    return Data;
}

int main()
{

    int WindowDimensions[2] = { 720, 480 };
    int Width = 720;
    int Height = 480;
    InitWindow(WindowDimensions[0], WindowDimensions[1], "Dapper Dasher");
    SetTargetFPS(60);

    int Velocity = {0};

    // pixels / second
    int JumpVelocity = {-600};

    // pixels / second / second
    const int Gravity = {1'000};

    bool bIsInAir = false;

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX = 0.f;
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX = 0.f;
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX = 0.f;

    Texture2D NebulaTexture = LoadTexture("textures/12_nebula_spritesheet.png");

    const int NumberOfNebulae = { 7 };
    
    AnimationData NebulaeArray[NumberOfNebulae] = { };

    for (int i = 0, t = 0; i < NumberOfNebulae; i++, t +=500)
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

    float finishLine = { NebulaeArray[NumberOfNebulae - 1].pos.x };
    
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

    bool bCollided = { false };

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        const float DeltaTime = { GetFrameTime() };
        bgX -= 20 * DeltaTime;
        mgX -= 40 * DeltaTime;
        fgX -= 80 * DeltaTime;

        if(bgX <= -background.width*4)
        {
            bgX = 0.f;
        }

        if(mgX <= -background.width*4)
        {
            mgX = 0.f;
        }

        if(fgX <= -foreground.width*2)
        {
            fgX = 0.f;
        }
 
        Vector2 bg1pos = {bgX,0};
        Vector2 bg2pos = {bgX + background.width * 4 , 0};
        DrawTextureEx(background, bg1pos, 0.f, 4.f, WHITE);
        DrawTextureEx(background, bg2pos, 0.f, 4.f, WHITE);

        Vector2 mg1pos = {mgX,0};
        Vector2 mg2pos = {mgX + midground.width * 4 , 0};
        DrawTextureEx(midground, mg1pos, 0.f, 4.f, WHITE);
        DrawTextureEx(midground, mg2pos, 0.f, 4.f, WHITE);

        Vector2 fg1pos = {fgX,100};
        Vector2 fg2pos = {fgX + foreground.width * 2 , 100};
        DrawTextureEx(foreground, fg1pos, 0.f, 2.f, WHITE);
        DrawTextureEx(foreground, fg2pos, 0.f, 2.f, WHITE);

        // Scarfy is in air ?
        if(bScarfyOnGround(ScarfyData, Height))
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

        finishLine += NebulaVelocity * DeltaTime;

        for (int i = 0; i < NumberOfNebulae; i++)
        {
            NebulaeArray[i] = updateAnimData(NebulaeArray[i], DeltaTime, 7);
        }
        
        // Update Scarfy's jumping position value based on velocity * deltatime
        ScarfyData.pos.y += Velocity * DeltaTime;

        if(!bIsInAir)
        {
            ScarfyData = updateAnimData(ScarfyData, DeltaTime, 5);  
        }

        for( AnimationData Nebula : NebulaeArray )
        {
            float pad = 50.f;
            Rectangle nebRec { Nebula.pos.x + pad, Nebula.pos.y + pad, Nebula.rec.width - 2* pad, Nebula.rec.height - 2 * pad };
            Rectangle ScarfyRec = { ScarfyData.pos.x, ScarfyData.pos.y, ScarfyData.rec.width, ScarfyData.rec.height };
            if(CheckCollisionRecs(nebRec, ScarfyRec))
            {
                bCollided = true;
            }
        }

        if(!bCollided)
        {
            // Draw Scarfy
            DrawTextureRec(Scarfy, ScarfyData.rec, ScarfyData.pos, WHITE);
            if(ScarfyData.pos.x >= finishLine)
            {
                DrawText("YOU WIN!", 100 , Height/2, 80, BLUE);
            }
        }
        else
        {
                DrawText("YOU LOSE....", 100 , Height/2, 80, BLUE);
        }
         // Draw Nebulae
        for (int i = 0; i < NumberOfNebulae; i++)
        {
            DrawTextureRec(NebulaTexture, NebulaeArray[i].rec, NebulaeArray[i].pos, WHITE);
        }
      
        EndDrawing();
    }

    UnloadTexture(midground);
    UnloadTexture(foreground);
    UnloadTexture(background);
    UnloadTexture(NebulaTexture);
    UnloadTexture(Scarfy);
    CloseWindow();

}