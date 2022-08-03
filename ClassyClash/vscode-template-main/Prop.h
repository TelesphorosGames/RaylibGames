class Prop
{
public:
    Prop(Vector2 pos, Texture2D tex);

    void Render(Vector2 inKnightPosition);

    Rectangle GetCollisionRec(Vector2 inKnightPosition);


private:


    Texture2D Texture{};
    Vector2 WorldPosition{};
    float Scale{4.f};

    Vector2 ScreenPosition{};


};