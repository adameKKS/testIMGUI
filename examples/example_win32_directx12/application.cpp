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
        ImVec2 center(WinPos.x + WinSize.x/2, WinPos.y + WinSize.y /2) ;
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->PushClipRect(WinPos, ImVec2(WinSize.x+WinPos.x,WinSize.y+WinPos.y));

        ImVec2 ground(WinPos.x+WinSize.x,WinPos.y + WinSize.y);

        ImVec2 jula(center.x, center.y);

        static myApp::rect prostokont(jula, 50.f, 40.f);
        //static myApp::rect kwadrat(ImVec2(jula.x + 50.f, jula.y + 50.f), 30.f, 30.f); 

        //mechanics
        prostokont.Update(ground,WinPos);       
        //kwadrat.Update(ground, WinPos);
        prostokont.DrawRect(draw_list);
        //kwadrat.DrawRect(draw_list);

        ///visu
        prostokont.GetVel();
        prostokont.GetAcc();
        prostokont.GetCenter();
        
        draw_list->PopClipRect();

        ImGui::End();
    }
}
/*
NOTES:
-when vel=0.5 and f1 is clicked to stop the block entirely, the sign at the velocty changes since f1 click= --velX. To be updated: f1 press should stop the block entirely without moving in any direction and if we want the movement to be renewed, the previous direction should be preserved.
*/
