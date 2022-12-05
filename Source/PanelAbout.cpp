#include "PanelAbout.h"

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

#include <GL/glew.h>
#include <string>

#include "Globals.h"


bool PanelAbout::Draw()
{
	if (!m_Open)
	{
		return true;
	}

	ImGui::SetNextWindowSize(ImVec2(385, 265), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(0, 18), ImGuiCond_Once);
	ImGui::Begin(m_Title, &m_Open);

	ImGui::Text("NAME:");
	ImGui::Text(TITLE);
	ImGui::Text("Developed by David Castro Salazar.");
	ImGui::Separator();

	ImGui::Text("The libraries used:");
	ImGui::TextColored(ImVec4(147, 0, 255, 1), "	- SDL");
	ImGui::TextColored(ImVec4(147, 0, 255, 1), "	- GLEW");
	ImGui::TextColored(ImVec4(147, 0, 255, 1), "	- MathGeoLib");
	ImGui::TextColored(ImVec4(147, 0, 255, 1), "	- ImGui");
	ImGui::TextColored(ImVec4(147, 0, 255, 1), "	- DebugDraw");
	ImGui::TextColored(ImVec4(147, 0, 255, 1), "	- DirectXTex");
	ImGui::TextColored(ImVec4(147, 0, 255, 1), "	- Assimp");
	ImGui::Separator();

	ImGui::Text("Copyright (c) 2022 David Castro Salazar");
	ImGui::Separator();


	ImGui::End();
	return true;
}

PanelAbout::PanelAbout(const char* InTitle) : Panel(InTitle)
{
	m_Open = false;
}
