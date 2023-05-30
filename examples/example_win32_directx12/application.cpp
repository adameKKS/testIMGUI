
#define IMGUI_DEFINE_MATH_OPERATORS // Access to math operators

#include "application.h"
#include <math.h>
#include "imgui.h"
#include "imgui_internal.h"

#include "fx.inl"

namespace myApp {
    void RenderUI()
    {
        ImVec2 size(320.f, 180.f);
        ImGui::SetNextWindowSize(size);
        ImGui::Begin("buziaczki adamek");
        ImGui::Text("size variable: %f, %f",size.x,size.y);
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
}
