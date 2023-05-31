#pragma once
#include <imgui.h>
extern int counter;
extern float velocity;
extern float gravity;

namespace myApp {
    void RenderUI();
    void FxTestBed();
    class rect
    {
    public:
        rect(ImVec2& center, float Horizontal, float Vertical);
        void GetCenter();
        void DrawRect(ImDrawList* draw_list, ImVec2 WinPos, ImVec2 WinSize); // cemterPos allows us to modify the position of the rect- centerpos.x and centerpos.y are added to the draw func so every time the function is executed the updated position is rendered.
        float rect::Jump();
        float rect::EndJump();
        void rect::Update(float velocity, float gravity);
        
    private:
        ImVec2 center;
        float Horizontal;
        float Vertical;
    };
}

