#pragma once

#include <vector>
#include "ModuleTexture.h"
#include "Math/float3.h"

class aiMesh;

class Mesh
{

public:
	Mesh(const aiMesh* mesh);
	~Mesh();
	void LoadVBO(const aiMesh* InMesh);
	void LoadEBO(const aiMesh* InMesh);
	void CreateVAO();
	void Draw(const std::vector<TextureInfo> InModelTexture);
	float3 GetCenterOfMesh();

private:

	unsigned m_vbo = 0;
	unsigned m_vao = 0;
	unsigned m_ebo = 0;
	int m_NumVetices = 0;
	int m_NumIndices = 0;
	int m_MaterialIndex = 0;
	float3 m_CenterOfMesh = { 0,0,0 };
	
};

