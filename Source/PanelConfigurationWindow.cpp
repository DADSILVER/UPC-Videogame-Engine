#include "PanelConfigurationWindow.h"

#include "imgui.h"

#include "Application.h"

#include "ModuleEditor.h"

PanelConfigurationWindow::PanelConfigurationWindow(const char* InTitle) : Panel(InTitle)
{
}

bool PanelConfigurationWindow::Draw()
{

    if (!m_Open)
    {
        return true;
    }
    ImGui::SetNextWindowSize(ImVec2(300, 500), ImGuiCond_Once);
    if (!ImGui::Begin(m_Title, &m_Open))
    {
        ImGui::End();
        return false;
    }
    
    if (ImGui::CollapsingHeader("Application"))
    {
        std::vector<float> fpsLogs = App->m_Editor->GetFps();
        std::vector<float> msLogs = App->m_Editor->GetMs();
        char title[25];
        sprintf_s(title, 25, "Framerate %.1f", fpsLogs[fpsLogs.size() - 1]);
        ImGui::PlotHistogram("##framerate", &fpsLogs[0], 100, 0, title, 0.0f, 200.0f, ImVec2(310.0f, 100.0f));
        sprintf_s(title, 25, "Miliseconds %.1f", msLogs[msLogs.size() - 1]);
        ImGui::PlotHistogram("##framerate", &msLogs[0], 100, 0, title, 0.0f, 200.0f, ImVec2(310.0f, 100.0f));
    }
    ImGui::End();


	return true;
}
