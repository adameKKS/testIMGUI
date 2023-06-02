#include "application.h"
#include <iostream>

namespace myApp
{
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

    void rect::SetVelX(float velX)
    {
        this->velX = velX;
    }
    void rect::SetVelY(float velY)
    {
        this->velY = velY;
    }

    void rect::DrawRect(ImDrawList* draw_list)
    {
        draw_list->AddRectFilled(ImVec2(center.x - Horizontal, center.y - Vertical), ImVec2(center.x + Horizontal, center.y + Vertical), IM_COL32(255, 128, 0, 255));
    }
    void rect::Jump()
    {

        if (height)return; // so EndJumps activates when there is "height" limit achieved
        if (onGround) // nie wiem czy to ma sens ale przez to dzia³a lepiej
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
        ImVec2 newCenter(center.x + velX, center.y + velY);


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

        if (newCenter.x + Horizontal >= ground.x || newCenter.x - Horizontal <= winpos.x)
        {
            velX *= -1;
        }

        if (ImGui::IsKeyDown(ImGuiKey_F1))SetVelX((velX >= 0) ? --velX:++velX);
        if (ImGui::IsKeyDown(ImGuiKey_F2))SetVelX((velX > 0) ? ++velX : --velX);


        this->center.y = newCenter.y;
        this->center.x = newCenter.x;

        if (ImGui::IsKeyDown(ImGuiKey_UpArrow)) this->Jump();
        if (!ImGui::IsKeyDown(ImGuiKey_UpArrow) || height) this->EndJump();

        ImGui::Text("newCenter: %f", newCenter.y);
        ImGui::Text("center.y + Vertical: %f, winpos.y + winsize.y: %f", center.y + Vertical, ground.y);
    }
}
