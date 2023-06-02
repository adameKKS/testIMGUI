#pragma once
#include <imgui.h>
extern int counter;
extern float gravity;

namespace myApp {
    void RenderUI();

    class rect
    {
    public:
        rect(ImVec2& center, float Horizontal, float Vertical);
        void GetCenter();
        void GetVel();
        void GetAcc();

        void SetVelX(float velX);
        void SetVelY(float velY);
        
        void DrawRect(ImDrawList* draw_list); // cemterPos allows us to modify the position of the rect- centerpos.x and centerpos.y are added to the draw func so every time the function is executed the updated position is rendered.
        void Jump();
        void EndJump();
        void Update(ImVec2& ground, ImVec2& winpos);
        
    private:
        ImVec2 center;
        float Horizontal;
        float Vertical;
        float velY;
        float velX = 4.5f;
        float acc;
        float gravity = .09f;
        bool onGround;
        bool height= false;
    };
}

