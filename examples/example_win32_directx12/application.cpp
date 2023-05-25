#include "application.h"
#include "imgui.h"
#include <math.h>

namespace myApp {
    void RenderUI()
    {
        ImGui::Begin("buziaczki adamek");
        ImGui::Button("dupaduapas");
        ImVec2 p1(20.f, 20.f);
        ImVec2 p2(40.f, 40.f);
        ImDrawList* d;
        d->AddRect(p1, p2,11);
        static float val = 0.6f;
        ImGui::DragFloat("value", &val);
        ImGui::End();
    }

}
