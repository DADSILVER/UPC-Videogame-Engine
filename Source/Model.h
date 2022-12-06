#pragma once
#include <vector>
#include "DirectXTex.h"
#include "ModuleTexture.h"
#include "Math/float3.h"
#include "Mesh.h"

struct aiScene;
struct aiMesh;



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
	inline const std::string& GetName() { return m_Name; }
	inline const std::vector<Mesh*>& GetMeshes() { return m_Meshes; }
	inline const std::vector<TextureInfo>& GetTextures() { return m_Material; }
	inline float4x4& GetModelMatrix() { return m_Meshes[0]->GetModelMatrix(); }
	inline const float3& GetRotationModel() { return m_Meshes[0]->GetRotation(); }
	inline const float3& GetScaleModel() { return m_Meshes[0]->GetScale(); }
	void SetRotationModel(const float3& InRotation);
	void SetScaleModel(const float3& InScale);

private:
	std::vector<TextureInfo> m_Material;
	std::vector<Mesh*> m_Meshes;
	
	std::string m_Name = "";
	float3 m_CenterOfModel = { 0,0,0 };
	float3 m_InitVisionPos = { 0,0,0 };
};

