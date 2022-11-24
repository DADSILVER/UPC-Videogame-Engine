#pragma once

#include <vector>

class aiMesh;
class Mesh
{

public:
	void LoadVBO(const aiMesh* InMesh);
	void LoadEBO(const aiMesh* InMesh);
	void CreateVAO();
	void Draw(const std::vector<unsigned>& InModelTexture);

private:

	unsigned m_vbo = 0;
	unsigned m_vao = 0;
	unsigned m_ebo = 0;
	int m_NumVetices = 0;
	int m_NumIndices = 0;
	int m_MaterialIndex = 0;
	
};

