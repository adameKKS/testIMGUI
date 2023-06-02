#pragma once
#include <imgui.h>
extern int counter;
extern float gravity;

namespace myApp {
    void RenderUI();
    void FxTestBed();
    class rect
    {
    public:
        rect(ImVec2& center, float Horizontal, float Vertical);
        void GetCenter();
        void GetVel();
        void rect::GetAcc();

        void DrawRect(ImDrawList* draw_list); // cemterPos allows us to modify the position of the rect- centerpos.x and centerpos.y are added to the draw func so every time the function is executed the updated position is rendered.
        void rect::Jump();
        void rect::EndJump();
        void rect::Update(ImVec2& ground, ImVec2& winpos);
        
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

