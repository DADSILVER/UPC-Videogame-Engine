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

	inline const float3 GetCenterOfMesh()	{return (m_MatrixModel * m_CenterOfMesh.ToPos4()).xyz();}
	inline const float3 GetMaxVertices()	{return (m_MatrixModel * m_MaxOfMesh.ToPos4()).xyz();}
	inline const float3 GetMinVertices()	{return (m_MatrixModel * m_MinOfMesh.ToPos4()).xyz();}
	inline const int& GetNumVertices()		{return m_NumVetices;}
	inline const int& GetNumOfTriangles()	{return m_NumTriangles;}

	inline void SetModelMatrix(const float4x4& InModel) { m_MatrixModel = InModel;}
	inline float4x4& GetModelMatrix() { return m_MatrixModel; }
	inline void SetRotation(const float3& InRotation) { m_RotationAngles = InRotation; }
	inline const float3& GetRotation() { return m_RotationAngles; }
	inline void SetScale(const float3& InScale) { m_Scale = InScale; }
	inline const float3& GetScale() { return m_Scale; }

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
	float3 m_RotationAngles = { 0,0,0 };
	float3 m_Scale = { 1,1,1 };


	float4x4 m_MatrixModel;
	
};

