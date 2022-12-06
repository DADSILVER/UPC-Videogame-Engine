#pragma once

#include <vector>
#include "ModuleTexture.h"
#include "Math/float3.h"
#include "Math/float4x4.h"

struct aiMesh;

class Mesh
{

public:
	Mesh(const aiMesh* InMesh);
	~Mesh();
	void LoadVBO(const aiMesh* InMesh);
	void LoadEBO(const aiMesh* InMesh);
	void CreateVAO();
	void Draw(const std::vector<TextureInfo>& InModelTexture);

	inline const float3 GetCenterOfMesh()	{return (m_model * m_CenterOfMesh.ToPos4()).xyz();}
	inline const float3 GetMaxVertices()	{return (m_model * m_MaxOfMesh.ToPos4()).xyz();}
	inline const float3 GetMinVertices()	{return (m_model * m_MinOfMesh.ToPos4()).xyz();}
	inline const int& GetNumVertices()		{return m_NumVetices;}
	inline const int& GetNumOfTriangles()	{return m_NumTriangles;}

	inline void SetModelMatrix(const float4x4& InModel) {m_model = InModel;}

private:

	unsigned m_vbo = 0;
	unsigned m_vao = 0;
	unsigned m_ebo = 0;

	int m_NumVetices = 0;
	int m_NumTriangles = 0;
	int m_MaterialIndex = 0;

	float3 m_CenterOfMesh = { 0,0,0 };
	float3 m_MaxOfMesh = { 0,0,0 };
	float3 m_MinOfMesh = { 0,0,0 };


	float4x4 m_model;
	
};

