
#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators

#include "application.h"
#include <math.h>
#include "imgui.h"
#include "imgui_internal.h"
#include <iostream>

#include "fx.inl"


namespace myApp {
     void RenderUI()
    {
        counter++;
        const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y),ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(main_viewport->Size.x, main_viewport->Size.y), ImGuiCond_Always);
        ImGui::Begin("buziaczki adamek");
       
        ImVec2 WinSize = ImGui::GetWindowSize();
        ImVec2 WinPos = ImGui::GetWindowPos();

        ImGui::Text("WinSize: %f, %f", WinSize.x, WinSize.y);
        ImGui::Text("WinPos: %f, %f", WinPos.x, WinPos.y);
        ImGui::Text("Velocity: %f", velocity);
        ImVec2 center(WinPos.x + WinSize.x/2, WinPos.y + WinSize.y /2) ;
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->PushClipRect(WinPos, WinSize);
        /*draw_list->AddRectFilled(
            ImVec2(center.x-50.f,center.y-50.f),
            ImVec2(center.x+50.f,center.y+50.f),
            IM_COL32(255, 128, 0, 255));*/
       

        ImVec2 jula(center.x, center.y);

        static myApp::rect prostokont(jula, 50.f, 70.f);
        prostokont.GetCenter();

        if (ImGui::IsKeyDown(ImGuiKey_UpArrow)) velocity = prostokont.Jump();
        if (!ImGui::IsKeyDown(ImGuiKey_UpArrow)) velocity = prostokont.EndJump();
        prostokont.Update(velocity, gravity);
        prostokont.DrawRect(draw_list, WinPos, WinSize);
        
        draw_list->PopClipRect();
        ImGui::End();
    }


    void FxTestBed()
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Begin("FX", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImVec2 size(320.0f, 180.0f);
        ImGui::InvisibleButton("canvas", size);
        ImVec2 p0 = ImGui::GetItemRectMin();
        ImVec2 p1 = ImGui::GetItemRectMax();
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->PushClipRect(p0, p1);

        ImVec4 mouse_data;
        mouse_data.x = (io.MousePos.x - p0.x) / size.x;
        mouse_data.y = (io.MousePos.y - p0.y) / size.y;
        mouse_data.z = io.MouseDownDuration[0];
        mouse_data.w = io.MouseDownDuration[1];

        FX(draw_list, p0, p1, size, mouse_data, (float)ImGui::GetTime());
        draw_list->PopClipRect();
        ImGui::End();
    }







    rect::rect(ImVec2& center, float Horizontal, float Vertical)
        :center(center)
    {
        this->Horizontal = Horizontal;
        this->Vertical = Vertical;
        std::cout << "Tworze obiekta" << std::endl;
    };
    void rect::GetCenter()
    {
        ImGui::Text("TopLeft: %f, %f", center.x, center.y);
    }
    void rect::DrawRect(ImDrawList* draw_list, ImVec2 WinPos, ImVec2 WinSize)
    {
        draw_list->AddRectFilled(ImVec2(center.x-Horizontal,center.y-Vertical), ImVec2(center.x + Horizontal, center.y + Vertical), IM_COL32(255, 128, 0, 255));
    }
    float rect::Jump()
    {
        return velocity = -12.f;
    }
    float rect::EndJump()
    {
        return (velocity < -6.f) ? velocity = 6.f : velocity;
    }
    void rect::Update(float velocity, float gravity)
    {
        velocity += gravity;
        this->center.y += velocity;
    }
}
