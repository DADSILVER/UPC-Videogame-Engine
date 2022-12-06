#include <assimp/mesh.h>

#include "Mesh.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"
#include "ModuleProgram.h"

#include <GL/glew.h>
#include <Math/float2.h>


Mesh::Mesh(const aiMesh* InMesh)
{
	m_model = float4x4::FromTRS(float3(0.0f, 0.0f, 0.0f),
		//float4x4::RotateX(-pi/2),
		float4x4::RotateX(0),
		//float3(0.01f, 0.01f, 0.01f)
		float3(1.0f, 1.0f, 1.0f)
	);
	LoadVBO(InMesh);
	LoadEBO(InMesh);
	m_MaterialIndex = InMesh->mMaterialIndex;
	CreateVAO();
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::LoadVBO(const aiMesh* InMesh)
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned buffer_size = vertex_size * InMesh->mNumVertices;

	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);

	unsigned position_size = sizeof(float) * 3 * InMesh->mNumVertices;

	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, InMesh->mVertices);

	if (InMesh->mNumVertices > 0) {
		m_MaxOfMesh.x += InMesh->mVertices[0].x;
		m_MaxOfMesh.y += InMesh->mVertices[0].y;
		m_MaxOfMesh.z += InMesh->mVertices[0].z;
		m_MinOfMesh = m_MaxOfMesh;
	}

	for (unsigned i = 1; i < InMesh->mNumVertices; ++i)
	{
		//Chekking max
		if (InMesh->mVertices[i].x > m_MaxOfMesh.x)
		{
			m_MaxOfMesh.x = InMesh->mVertices[i].x;
		}
		if (InMesh->mVertices[i].y > m_MaxOfMesh.y)
		{
			m_MaxOfMesh.y = InMesh->mVertices[i].y;
		}
		if (InMesh->mVertices[i].z > m_MaxOfMesh.z)
		{
			m_MaxOfMesh.z = InMesh->mVertices[i].z;
		}

		//Chekking min
		if (InMesh->mVertices[i].x < m_MinOfMesh.x)
		{
			m_MinOfMesh.x = InMesh->mVertices[i].x;
		}
		if (InMesh->mVertices[i].y < m_MinOfMesh.y)
		{
			m_MinOfMesh.y = InMesh->mVertices[i].y;
		}
		if (InMesh->mVertices[i].z < m_MinOfMesh.z)
		{
			m_MinOfMesh.z = InMesh->mVertices[i].z;
		}
	}

	m_CenterOfMesh = (m_MaxOfMesh + m_MinOfMesh) / 2;

	unsigned uv_offset = position_size;
	unsigned uv_size = sizeof(float) * 2 * InMesh->mNumVertices;
	float2* uvs = (float2*)(glMapBufferRange(GL_ARRAY_BUFFER, uv_offset, uv_size, GL_MAP_WRITE_BIT));

	for (unsigned i = 0; i < InMesh->mNumVertices; ++i)
	{
		uvs[i] = float2(InMesh->mTextureCoords[0][i].x, InMesh->mTextureCoords[0][i].y);
	}

	glUnmapBuffer(GL_ARRAY_BUFFER);
	m_NumVetices = InMesh->mNumVertices;
}

void Mesh::LoadEBO(const aiMesh* InMesh)
{
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	unsigned index_size = sizeof(unsigned) * InMesh->mNumFaces * 3;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_size, nullptr, GL_STATIC_DRAW);

	unsigned* indices = (unsigned*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	float x = 0, y = 0, z = 0;
	for (unsigned i = 0; i < InMesh->mNumFaces; ++i)
	{
		assert(InMesh->mFaces[i].mNumIndices == 3); // note: assume triangles = 3 indices per face
		*(indices++) = InMesh->mFaces[i].mIndices[0];
		*(indices++) = InMesh->mFaces[i].mIndices[1];
		*(indices++) = InMesh->mFaces[i].mIndices[2];
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	m_NumTriangles = InMesh->mNumFaces;
}

void Mesh::CreateVAO()
{
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 3 * m_NumVetices));
}

void Mesh::Draw(const std::vector<TextureInfo>& InModelTexture)
{
	unsigned program = App->m_Renderer->m_Program;
	

	glUseProgram(program);

	glUniformMatrix4fv(2, 1, GL_TRUE, &m_model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &App->m_Camera->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(0, 1, GL_TRUE, &App->m_Camera->GetProjectionMatrix()[0][0]);


	//Enable texture
	glActiveTexture(GL_TEXTURE0);
	if (InModelTexture.size() > 0)
	{
		glBindTexture(GL_TEXTURE_2D, InModelTexture[m_MaterialIndex].m_Texture);
	}
	else 
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glUniform1i(glGetUniformLocation(program, "mytexture"), 0);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glDrawElements(GL_TRIANGLES, m_NumTriangles*3, GL_UNSIGNED_INT, nullptr);
	
}
