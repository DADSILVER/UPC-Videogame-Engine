#include "PanelConfigurationWindow.h"

#include "imgui.h"

#include "Application.h"

#include "ModuleEditor.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

#include <SDL_version.h>
#include <SDL_cpuinfo.h>
#include <GL/glew.h>
#include <SDL_gesture.h>

//#include <imgui_impl_sdl.cpp>

#pragma comment(lib, "dxgi")


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

	if (ImGui::CollapsingHeader("Renderer"))
	{

		ImGui::TextUnformatted("Change the color of the background:");

		float background[3] = { App->m_Renderer->M_BackGroundColor[0], App->m_Renderer->M_BackGroundColor[1], App->m_Renderer->M_BackGroundColor[2] };
		ImGui::SetNextItemWidth(195);
		if (ImGui::ColorPicker3("##background##1", (float*)&background, ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha))
		{
			App->m_Renderer->M_BackGroundColor[0] = background[0];
			App->m_Renderer->M_BackGroundColor[1] = background[1];
			App->m_Renderer->M_BackGroundColor[2] = background[2];
		}
		ImGui::SameLine();
		ImGui::SetNextItemWidth(195);
		if (ImGui::ColorPicker3("##background##2", (float*)&background, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha))
		{
			App->m_Renderer->M_BackGroundColor[0] = background[0];
			App->m_Renderer->M_BackGroundColor[1] = background[1];
			App->m_Renderer->M_BackGroundColor[2] = background[2];
		}
		ImGui::Separator();


		ImGui::TextUnformatted("Change the color of the grid:");

		float grid[3] = { App->m_Renderer->m_GridColor[0], App->m_Renderer->m_GridColor[1], App->m_Renderer->m_GridColor[2] };
		ImGui::SetNextItemWidth(195);
		if (ImGui::ColorPicker3("##grid##1", (float*)&grid, ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha))
		{
			App->m_Renderer->m_GridColor[0] = grid[0];
			App->m_Renderer->m_GridColor[1] = grid[1];
			App->m_Renderer->m_GridColor[2] = grid[2];
		}
		ImGui::SameLine();
		ImGui::SetNextItemWidth(195);
		if (ImGui::ColorPicker3("##grid##2", (float*)&grid, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha))
		{
			App->m_Renderer->m_GridColor[0] = grid[0];
			App->m_Renderer->m_GridColor[1] = grid[1];
			App->m_Renderer->m_GridColor[2] = grid[2];
		}
		ImGui::Separator();

	}

    if (ImGui::CollapsingHeader("Window"))
    {

        bool fullscreen = App->m_Window->GetTypeScreen() == FULLSCREEN;
        bool resizable = App->m_Window->GetTypeScreen() == RESIZABLE;
        bool borderless = App->m_Window->GetTypeScreen() == BORDERLESS;

        float brightness = App->m_Window->GetBrightness();

        if (ImGui::SliderFloat("Brightness", &brightness, 0, 1)) {
            App->m_Window->SetBrightness(brightness);
        }

        int widht = App->m_Window->GetWidth();
        if (ImGui::SliderInt("Widht", &widht, 0, App->m_Window->GetMaxWidht())) {
            App->m_Window->SetWidth(widht);
        }

        int height = App->m_Window->GetHeight();
        if (ImGui::SliderInt("Height", &height, 0, App->m_Window->GetMaxHeight())) {
            App->m_Window->SetHeight(height);
        }

        if (ImGui::Checkbox("FULLSCREEN   |  ", &fullscreen))
        {
            App->m_Window->SetTypeScreen(FULLSCREEN);
        }
        ImGui::SameLine();
        if (ImGui::Checkbox("RESIZABLE", &resizable))
        {
            App->m_Window->SetTypeScreen(RESIZABLE);
        }

        if (ImGui::Checkbox("BORDERLESS   |  ", &borderless))
        {
            App->m_Window->SetTypeScreen(BORDERLESS);
        }
    }

	if (ImGui::CollapsingHeader("Hardware")) {
        SDL_version sdl_ver;
        SDL_VERSION(&sdl_ver);

        ImGui::Text("SDL version:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(147, 0, 255, 1.0f), "%u.%u.%u", sdl_ver.major, sdl_ver.minor, sdl_ver.patch);
        ImGui::Separator();

        ImGui::Text("CPUs:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(147, 0, 255, 1.0f), "%u (Cache: %ukb)", SDL_GetCPUCount(), SDL_GetCPUCacheLineSize());
        ImGui::Text("System RAM:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(147, 0, 255, 1.0f), "%uGb", SDL_GetSystemRAM());
		
		ImGui::Separator();

		SDL_GetCurrentVideoDriver();
		ImGui::Text("GPU:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(147, 0, 255, 1.0f), "%s", glGetString(GL_RENDERER));

		ImGui::Text("Brand:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(147, 0, 255, 1.0f), "%s", glGetString(GL_VENDOR));

		ImGui::Separator();
	}

    ImGui::End();


	return true;
}
