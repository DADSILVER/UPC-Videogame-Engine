#pragma once
#include <vector>
#include "DirectXTex.h"
#include "ModuleTexture.h"
#include "Math/float3.h"

struct aiScene;
struct aiMesh;
class Mesh;


class Model
{


public:
	void Load(const char* inFileName);
	void LoadMeshes(const aiScene* InScene);
	void LoadMaterials(const aiScene* inScene,const char* InFileName);
	void Draw();

	const float3 GetCenterOfModel();
	const float3& GetInitVisionPos();
	void SetModelMatrix(const float4x4& InModel);
	const std::string& GetName() { return m_Name; }
	const std::vector<Mesh*>& GetMeshes() { return m_Meshes; }
	const std::vector<TextureInfo>& GetTextures() { return m_Material; }


private:
	std::vector<TextureInfo> m_Material;
	std::vector<Mesh*> m_Meshes;
	
	std::string m_Name = "";
	float3 m_CenterOfModel = { 0,0,0 };
	float3 m_InitVisionPos = { 0,0,0 };
};

