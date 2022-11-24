#include "assimp/cimport.h"
#include "assimp/scene.h"
#include <assimp/postprocess.h> 
#include "assimp/material.h"

#include "Model.h"



#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"


void Model::Load(const char* inFileName)
{
	const aiScene* scene = aiImportFile(inFileName, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene)
	{
		LoadMaterials(scene);
		LoadMeshes(scene->mMeshes, scene->mNumMeshes);
	}
	else
	{
		engLOG("Error loading %s: %s", inFileName, aiGetErrorString());
	}
}

void Model::LoadMeshes(aiMesh** inMaterials, unsigned int inNumMaterials)
{

}


void Model::LoadMaterials(const aiScene* InScene)
{
	aiString file;
	
	m_Material.reserve(InScene->mNumMaterials);
	for (unsigned i = 0; i < InScene->mNumMaterials; ++i)
	{
		if (InScene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
		{
			App->m_texture->LoadTexture(file.data);
			m_Material.push_back(App->m_texture->GetImage());
		}
	}
}
