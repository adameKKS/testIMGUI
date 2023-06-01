
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
        /*draw_list->AddRectFilled(
            ImVec2(center.x-50.f,center.y-50.f),
            ImVec2(center.x+50.f,center.y+50.f),
            IM_COL32(255, 128, 0, 255));*/
        ImVec2 ground(WinPos.x+WinSize.x,WinPos.y + WinSize.y);

        ImVec2 jula(center.x, center.y);

        static myApp::rect prostokont(jula, 50.f, 40.f);
        
        //mechanics
        prostokont.Update(ground);
        
        
        prostokont.DrawRect(draw_list);

        ///visu
        prostokont.GetVel();
        prostokont.GetAcc();
        prostokont.GetCenter();
        
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
        acc = 0;
        std::cout << "Tworze obiekta" << std::endl;
    };
    void rect::GetCenter()
    {
        ImGui::Text("center.x: %f, center.y: %f", center.x, center.y);
    }
    void rect::GetVel()
    {
        ImGui::Text("velY: %f", velY);
    }
    void rect::GetAcc()
    {
        ImGui::Text("acc: %f", acc);
    }
    void rect::DrawRect(ImDrawList* draw_list)
    {
        draw_list->AddRectFilled(ImVec2(center.x-Horizontal,center.y-Vertical), ImVec2(center.x + Horizontal, center.y + Vertical), IM_COL32(255, 128, 0, 255));
    }
    void rect::Jump()
    {
        //if (onGround)
        //{
        //    ImGui::Text("ONGROUND WARNING!");
        //    velY = -2.f; //chujowe
        //    acc -= .3f;
        //    onGround = false;
        //}
        if (height)
        {
            ImGui::Text("HEIGHT WARNING!");
            acc = 0; //zastanowic sie czy tu nie warto dac += -.1 czy inna wartosc
            //velY = 0;
        }
        else if(!height && onGround) // nie wiem czy to ma sens ale przez to dzia³a lepiej
        {
            ImGui::Text("ONGROUND WARNING!");
            velY = -2.f; //chujowe chociaz????
            acc -= .1f;
            onGround = false;
        }
    }
    void rect::EndJump()
    {
        ImGui::Text("BUTTON RELEASED!!!!!!");
        if (!onGround)acc += .03f;
        else
        {
            velY = 0;
            acc = 0;
        }
    }
    void rect::Update(ImVec2 ground)
    {
        velY += gravity + acc;
        this->center.y += velY;
        float newCenter = center.y + velY;
        
        if (newCenter + Vertical >= ground.y)
        {
            acc = velY = 0;
            newCenter = ground.y - Vertical;
            onGround = true;                    
        }
        if (newCenter + Vertical <= ground.y / 1.3)
        {
            height = true;
        }
        else
        {
            height = false;
        }
        ImGui::Text("newCenter: %f", newCenter);
        this->center.y = newCenter;
        ImGui::Text("center.y + Vertical: %f, winpos.y + winsize.y: %f", center.y + Vertical, ground.y);
        ImGui::Text("ground.y: %f", ground.y);

        ImGui::Text("ground.y / 0.9: %f", (ground.y / 1.3));
        if (ImGui::IsKeyDown(ImGuiKey_UpArrow)) this->Jump();
        if (!ImGui::IsKeyDown(ImGuiKey_UpArrow)) this->EndJump();
    }
}
