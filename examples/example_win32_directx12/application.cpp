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
        static myApp::rect kwadrat(ImVec2(jula.x + 50.f, jula.y + 50.f), 30.f, 30.f);
        //mechanics
        prostokont.Update(ground,WinPos);       
        kwadrat.Update(ground, WinPos);
        prostokont.DrawRect(draw_list);
        kwadrat.DrawRect(draw_list);

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

        if (height)return; // so EndJumps activates when there is "height" limit achieved
        if(onGround) // nie wiem czy to ma sens ale przez to dzia³a lepiej
        {
            std::cout << "jestem tu" << std::endl;
            ImGui::Text("ONGROUND WARNING!");
            velY = -4.f; //chujowe chociaz????
            acc -= .3f;
            onGround = false;
        }
        else
        {
            acc = 0; //zastanowic sie czy tu nie warto dac += -.1 czy inna wartosc
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
    void rect::Update(ImVec2& ground, ImVec2& winpos)
    {
        velY += gravity + acc;
        this->center.y += velY;
        //float newCenter = center.y + velY;
        ImVec2 newCenter(center.x + velX,center.y + velY);

        
        if (newCenter.y + Vertical >= ground.y)
        {
            acc = velY = 0;
            newCenter.y = ground.y - Vertical;
            onGround = true;
            height = false;
        }
        if (newCenter.y + Vertical <= ground.y / 1.1) //parameter to tweak->height border
        {
            height = true;
            if (height)std::cout << "HEIGHT!!!!!" << std::endl;
        }

        if (newCenter.x + Horizontal >= ground.x || newCenter.x - Horizontal<=winpos.x)
        {
            velX *= -1;
        }


        this->center.y = newCenter.y;
        this->center.x = newCenter.x;

        if (ImGui::IsKeyDown(ImGuiKey_UpArrow)) this->Jump();
        if (!ImGui::IsKeyDown(ImGuiKey_UpArrow) || height) this->EndJump();

        ImGui::Text("newCenter: %f", newCenter.y);
        ImGui::Text("center.y + Vertical: %f, winpos.y + winsize.y: %f", center.y + Vertical, ground.y);
    }
}
