#pragma once
#include <vector>
#include "DirectXTex.h"
#include "ModuleTexture.h"
#include "Math/float3.h"

class aiScene;
class aiMesh;
class Mesh;


class Model
{


public:
	void Load(const char* inFileName);
	void LoadMeshes(const aiScene* InScene);
	void LoadMaterials(const aiScene* inScene);
	void Draw();

	float3 GetCenterOfModel();
	void SetModelMatrix(float4x4 InModel);


private:
	std::vector<TextureInfo> m_Material;
	std::vector<Mesh*> m_Meshes;
	float3 m_CenterOfModel = { 0,0,0 };
};

