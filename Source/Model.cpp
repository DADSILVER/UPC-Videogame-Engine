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


void Model::Load(const char* inFileName)
{
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
		m_CenterOfModel =+ mesh->GetCenterOfMesh();
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
			if (App->m_texture->LoadTexture(material))
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

float3 Model::GetCenterOfModel()
{
	return m_CenterOfModel;
}

 void Model::SetModelMatrix(float4x4 InModel)
{
	 for (size_t i = 0; i < m_Meshes.size(); i++)
	 {
		 m_Meshes[i]->SetModelMatrix(InModel);
	 }
}
