#include "PanelProperties.h"

#include "imgui.h"
#include <string>
#include "Math/float4x4.h"

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
	App->m_Renderer->GetWidth();
	App->m_Renderer->GetHeight();
	ImGui::SetNextWindowSize(ImVec2(300, (float)App->m_Renderer->GetHeight() / 1.5f), ImGuiCond_Always);
	ImGui::SetNextWindowPos(ImVec2((float)App->m_Renderer->GetWidth() - 300, 18) , ImGuiCond_Always);

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

	if (ImGui::CollapsingHeader("Transformation"))
	{
		float4x4 matrixModel = App->m_Renderer->GetModel().GetModelMatrix();
	
		//Set Position
		float position[3] = { matrixModel.x, matrixModel.y ,matrixModel.z };
		ImGui::DragFloat3("Position: ", position, 0.01f);

		//Set Rotation
		float4x4 rotation = float4x4::identity;
		float rot[3] = { App->m_Renderer->GetModel().GetRotationModel()[0], App->m_Renderer->GetModel().GetRotationModel()[1] ,App->m_Renderer->GetModel().GetRotationModel()[2] };
		ImGui::DragFloat3("Rotation: ", rot, 0.50f);
		rotation = float4x4::RotateX(rot[0] * DEGTORAD);
		rotation = rotation * float4x4::RotateY(rot[1] * DEGTORAD);
		rotation = rotation * float4x4::RotateZ(rot[2] * DEGTORAD);	
		App->m_Renderer->GetModel().SetRotationModel({ rot[0], rot[1], rot[2] });

		//SetScale
		float Scale[3] = { App->m_Renderer->GetModel().GetScaleModel()[0], App->m_Renderer->GetModel().GetScaleModel()[1] ,App->m_Renderer->GetModel().GetScaleModel()[2] };
		ImGui::DragFloat3("Scale; ", Scale, 0.01f);
		App->m_Renderer->GetModel().SetScaleModel({ Scale[0], Scale[1], Scale[2] });

		//Set TRS in the Matrix model
		App->m_Renderer->GetModel().SetModelMatrix(matrixModel.FromTRS({ position[0] , position[1] , position[2] }, rotation, { Scale[0] , Scale[1] , Scale[2] }));
	}

	ImGui::End();
    return true;
}
