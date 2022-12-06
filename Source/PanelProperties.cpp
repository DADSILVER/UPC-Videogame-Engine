#include "PanelProperties.h"

#include "imgui.h"
#include <string>

#include "Application.h"

#include "Mesh.h"

#include "Module.h"
#include "ModuleRender.h"


PanelProperties::PanelProperties(const char* InTitle) : Panel(InTitle)
{
}

bool PanelProperties::Draw()
{
	if (!m_Open)
	{
		return false;
	}

	ImGui::Begin(m_Title);

	ImGui::Text("Mesh Name:");
	ImGui::Text(App->m_Renderer->GetModel().GetName().c_str());

	if (ImGui::CollapsingHeader("Meshes"))
	{
		ImGui::Text("Number of meshes:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.0f, 185, 255, 1.0f), "%i", App->m_Renderer->GetModel().GetMeshes().size());
		ImGui::Separator();

		for (int i = 0; i < App->m_Renderer->GetModel().GetMeshes().size(); i++)
		{
			std::string SubTittle = "Mesh " + std::to_string(i+1);
			
			if (ImGui::TreeNode(SubTittle.c_str()))
			{
				ImGui::Text("Number of triangles:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(0.0f, 185, 255, 1.0f), "%i", App->m_Renderer->GetModel().GetMeshes()[i]->GetNumOfTriangles());
				ImGui::Text("Number of Vertices:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(0.0f, 185, 255, 1.0f), "%i", App->m_Renderer->GetModel().GetMeshes()[i]->GetNumVertices());
				ImGui::TreePop();
			}
			ImGui::Separator();
		}
	}

	if (ImGui::CollapsingHeader("Textures"))
	{
		ImGui::Text("Number of textures:");
		ImGui::SameLine();
		ImGui::TextColored(ImVec4(0.0f, 185, 255, 1.0f), "%i", App->m_Renderer->GetModel().GetTextures().size());
		ImGui::Separator();

		for (int i = 0; i < App->m_Renderer->GetModel().GetTextures().size(); i++)
		{
			std::string SubTittle = "Texture " + std::to_string(i + 1);

			if (ImGui::TreeNode(SubTittle.c_str()))
			{
				ImGui::Text("-  Id:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%u", App->m_Renderer->GetModel().GetTextures()[i].m_Texture);
				ImGui::SameLine();
				ImGui::Text("Name:");
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", App->m_Renderer->GetModel().GetTextures()[i].m_FileName.c_str());
				ImGui::Text("  ");
				ImGui::SameLine();
				ImGui::Image((void*)(intptr_t)App->m_Renderer->GetModel().GetTextures()[i].m_Texture, ImVec2(100, 100));

				ImGui::TreePop();
			}
			ImGui::Separator();
		}
	}
	ImGui::End();
    return true;
}
