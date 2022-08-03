#include "raylib.h"
#include "Prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex) :
Texture(tex),
WorldPosition(pos)

{
  
}

void Prop::Render(Vector2 inKnightPosition)
{
    ScreenPosition = Vector2Subtract(WorldPosition, inKnightPosition);

    DrawTextureEx(Texture, ScreenPosition, 1, Scale, WHITE);
}

Rectangle Prop::GetCollisionRec(Vector2 inKnightPosition)
{
    ScreenPosition = Vector2Subtract(WorldPosition, inKnightPosition);
    return Rectangle{ 
        ScreenPosition.x,
        ScreenPosition.y,
        Texture.width * Scale,
        Texture.height * Scale
    };
}