#include "assimp/cimport.h"
#include "assimp/scene.h"
#include <assimp/postprocess.h> 
#include "assimp/material.h"

#include "Model.h"
#include "Mesh.h"

#include "Globals.h"
#include "Application.h"

#include "ModuleTexture.h"
#include "ModuleEditor.h"

#include "Console.h"


void Model::Load(const char* inFileName)
{
	App->m_Editor->m_console.AddLog(engLOG("Model load from: %s\n", inFileName));
	const aiScene* scene = aiImportFile(inFileName, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		LoadMaterials(scene);
		LoadMeshes(scene);
	}
	else
	{
		App->m_Editor->m_console.AddLog(engLOG("Error loading %s: %s", inFileName, aiGetErrorString()));
	}
}

void Model::LoadMeshes(const aiScene* InScene)
{
	aiString file;

	m_Meshes.reserve(InScene->mNumMeshes);

	for (unsigned i = 0; i < InScene->mNumMeshes; ++i)
	{
		Mesh* mesh = new Mesh(InScene->mMeshes[i]);
		m_CenterOfModel += mesh->GetCenterOfMesh();
		m_Meshes.push_back(mesh);		
	}

}


void Model::LoadMaterials(const aiScene* InScene)
{
	aiString file;
	
	m_Material.reserve(InScene->mNumMaterials);
	for (unsigned i = 0; i < InScene->mNumMaterials; ++i)
	{
		if (InScene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			std::string filePath = file.data;
			size_t pos = 0;
			while ((pos = filePath.find(92)) != std::string::npos || (pos = filePath.find('/')) != std::string::npos)
			{
				filePath.erase(0, pos + 1);
			}
			filePath = "textures/" + filePath;
			TextureInfo material;
			material.m_FileName = filePath;
			if (App->m_Texture->LoadTexture(material))
			{
				m_Material.push_back(material);
			}
			
		}
	}
}

void Model::Draw()
{
	for (int i = 0; i < m_Meshes.size(); i++) {
		m_Meshes[i]->Draw(m_Material);
	}
}

const float3& Model::GetCenterOfModel()
{
	m_CenterOfModel = { 0,0,0 };
	for (unsigned i = 0; i < m_Meshes.size(); ++i)
	{
		m_CenterOfModel += m_Meshes[i]->GetCenterOfMesh();
	}
	return m_CenterOfModel / m_Meshes.size();
}

const float3& Model::GetInitVisionPos()
{
	float3 ActMaxVertes, ActMinVertes;
	if (m_Meshes.size() > 0)
	{
		ActMaxVertes = m_Meshes[0]->GetMaxVertices();
		ActMinVertes = m_Meshes[0]->GetMinVertices();
	}
	for (unsigned i = 1; i < m_Meshes.size(); ++i)
	{
		float3 MaxVertes = m_Meshes[i]->GetMaxVertices();
		float3 MinVertes = m_Meshes[i]->GetMinVertices();

		//Chekking max
		if (MaxVertes.x > ActMaxVertes.x)
		{
			ActMaxVertes.x = MaxVertes.x;
		}
		if (MaxVertes.y > ActMaxVertes.y)
		{
			ActMaxVertes.y = MaxVertes.y;
		}
		if (MaxVertes.z > ActMaxVertes.z)
		{
			ActMaxVertes.z = MaxVertes.z;
		}

		//Chekking min
		if (MinVertes.x < ActMinVertes.x)
		{
			ActMinVertes.x = MinVertes.x;
		}
		if (MinVertes.y < ActMinVertes.y)
		{
			ActMinVertes.y = MinVertes.y;
		}
		if (MinVertes.z < ActMinVertes.z)
		{
			ActMinVertes.z = MinVertes.z;
		}
	}
	m_InitVisionPos.Set(ActMaxVertes.x + (ActMaxVertes.x - ActMinVertes.x )/4,
		ActMaxVertes.y + (ActMaxVertes.y - ActMinVertes.y) / 4,
		ActMaxVertes.z + (ActMaxVertes.z - ActMinVertes.z) / 4);
	return m_InitVisionPos;
}

 void Model::SetModelMatrix(const float4x4& InModel)
{
	 for (size_t i = 0; i < m_Meshes.size(); i++)
	 {
		 m_Meshes[i]->SetModelMatrix(InModel);
	 }
}
