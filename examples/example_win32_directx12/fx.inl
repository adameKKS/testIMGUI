#include <complex>

ImVec2 shift(-2.12, -0.9);
float scale = 0.01;
float zoom_factor = 0.9;
size_t max_iter = 32;

void FX(ImDrawList* d, ImVec2 a, ImVec2 b, ImVec2 sz, ImVec4 m, float)
{
    /*if ((m.x >= 0 && m.x <= 1 && m.y >= 0 && m.y <= 1) && (m.z > 0 || m.w > 0))
    {
        float zf = m.z > 0 ? zoom_factor : 1 / zoom_factor;
        shift.x -= (m.x * sz.x * scale * (zf - 1));
        shift.y -= (m.y * sz.y * scale * (zf - 1));
        scale *= zf;
    }

    for (size_t x = 0; x < sz.x; ++x)
    {
        for (size_t y = 0; y < sz.y; ++y)
        {
            std::complex<double> c(shift.x + x / (sz.x - 1.0) * (sz.x * scale), shift.y + y / (sz.y - 1.0) * (sz.y * scale)), z;

            size_t iter;
            for (iter = 0; iter < max_iter && std::abs(z) < 2.0; ++iter)
                z = z * z + c;

            double v = std::log(iter) / std::log(max_iter - 1);
            if (iter < max_iter)
                d->AddRectFilled(ImVec2(a.x + x, a.y + y), ImVec2(a.x + x + 1, a.y + y + 1), IM_COL32((v * 255), 255 - (v * 255), 255, 255));
            else
                d->AddRectFilled(ImVec2(a.x + x, a.y + y), ImVec2(a.x + x + 1, a.y + y + 1), IM_COL32(0, 0, 0, 255));
        }
    }*/
    char txt_green[] = "text green";
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));
    ImGui::InputText("##text1", txt_green, sizeof(txt_green));
    ImGui::PopStyleColor();
    if (m.z!=-1.f)
    {
        d->AddRectFilled(a, b, IM_COL32(0, 128, 255, 255));
    }
    
}
