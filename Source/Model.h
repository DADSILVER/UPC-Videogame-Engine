#pragma once
#include <vector>
#include "DirectXTex.h"

class aiScene;
class Mesh;

class Model
{

public:
	void Load(const char* inFileName);
	void LoadMeshes(aiMesh** inMaterials, unsigned int inNumMaterials);
	void LoadMaterials(const aiScene* inScene);


private:
	//std::vector<DirectX::ScratchImage> m_Material;
	//std::vector<DirectX::ScratchImage*> m_Material;
	std::vector<Mesh*> m_Meshes;
};

