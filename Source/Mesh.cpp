#include <assimp/mesh.h>

#include "Mesh.h"

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"

#include <GL/glew.h>
#include <Math/float2.h>



void Mesh::LoadVBO(const aiMesh* InMesh)
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	unsigned vertex_size = (sizeof(float) * 3 + sizeof(float) * 2);
	unsigned buffer_size = vertex_size * InMesh->mNumVertices;

	glBufferData(GL_ARRAY_BUFFER, buffer_size, nullptr, GL_STATIC_DRAW);

	unsigned position_size = sizeof(float) * 3 * InMesh->mNumVertices;

	glBufferSubData(GL_ARRAY_BUFFER, 0, position_size, InMesh->mVertices);

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

	unsigned* indices = (unsigned*)(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_MAP_WRITE_BIT));

	for (unsigned i = 0; i < InMesh->mNumFaces; ++i)
	{
		assert(InMesh->mFaces[i].mNumIndices == 3); // note: assume triangles = 3 indices per face
		*(indices++) = InMesh->mFaces[i].mIndices[0];
		*(indices++) = InMesh->mFaces[i].mIndices[1];
		*(indices++) = InMesh->mFaces[i].mIndices[2];
	}
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	m_NumIndices = InMesh->mNumFaces * 3;
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

void Mesh::Draw(const std::vector<unsigned>& InModelTexture)
{
	unsigned program = App->m_renderer->m_program;
	float4x4 model = float4x4::identity;

	glUseProgram(program);

	glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &App->m_camera->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(0, 1, GL_TRUE, &App->m_camera->GetProjectionMatrix()[0][0]);


	//Enable texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, InModelTexture[m_MaterialIndex]);			
	glUniform1i(glGetUniformLocation(program, "mytexture"), 0);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}