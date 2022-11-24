#include "ModuleRenderExercise.h"
#include "Globals.h"
#include "SDL.h"
#include "libs/glew-2.1.0/include/GL/glew.h"
#include "Application.h"

#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"

#include "Model.h"


#include "Geometry/Frustum.h"
#include "Math/MathAll.h"
#include "DirectXTex.h"


ModuleRenderExercise::ModuleRenderExercise()
{
	m_model = float4x4::identity;
		
		float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		float3(2.0f, 1.0f, 1.0f));
}

bool ModuleRenderExercise::Init()
{
	//Load Model
	Model* BakerHause = new Model();
	BakerHause->Load("BakerHouse.fbx");

	//CreateFrustum();
	CreateTriangleVBO();

	m_program = App->m_program->CreateProgram();
	
	return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update()
{
	App->m_debugDraw->Draw(App->m_camera->GetViewMatrix(), App->m_camera->GetProjectionMatrix(), SCREEN_WIDTH, SCREEN_HEIGHT);
	RenderTriangle();
	return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
	SDL_GL_SwapWindow(App->m_window->window);
	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
	glDeleteProgram(m_program);
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_ebo);
	glDeleteTextures(1, &m_Texture);
	delete m_frustum;
	return true;
}

// This function must be called one time at creation of vertex buffer
void ModuleRenderExercise::CreateTriangleVBO()
{

	float m_vtx_data[] = { 
				// positions          // colors           // texture coords
				 0.5f,  0.5f, 0.0f,   /*1.0f, 0.0f, 0.0f,*/   1.0f, 1.0f,   // top right
				 0.5f, -0.5f, 0.0f,   /*0.0f, 1.0f, 0.0f,*/   1.0f, 0.0f,   // bottom right
				-0.5f, -0.5f, 0.0f,   /*0.0f, 0.0f, 1.0f,*/   0.0f, 0.0f,   // bottom left
				-0.5f,  0.5f, 0.0f,	  /*1.0f, 1.0f, 0.0f,*/   0.0f, 1.0f    // top left 
	};

	unsigned int m_index[] = {  // note that we start from 0!
		3, 1, 0,   // first triangle
		3, 2, 1    // second triangle
	};

	//vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	//vbo
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vtx_data), m_vtx_data, GL_STATIC_DRAW);
	
	//ebo
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_index), m_index, GL_STATIC_DRAW);

	//texture
	App->m_texture->LoadTexture("Test-image-Baboon.ppm");
	glGenTextures(1, &m_Texture);  
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	DirectX::TexMetadata metadata = App->m_texture->GetMetadata();
	int internalFormat, format, type;
	switch (metadata.format)
	{
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
		internalFormat = GL_RGBA8;
		format = GL_BGRA;
		type = GL_UNSIGNED_BYTE;
		break;
	case DXGI_FORMAT_B5G6R5_UNORM:
		internalFormat = GL_RGB8;
		format = GL_BGR;
		type = GL_UNSIGNED_BYTE;
		break;
	default:
		assert(false && "Unsupported format");
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, metadata.width, metadata.height, 0, format, type, App->m_texture->GetImage()->GetImage(0,0,0)->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	
}

void ModuleRenderExercise::RenderTriangle()
{

	glUseProgram(m_program);
	glUniformMatrix4fv(2, 1, GL_TRUE, &m_model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &App->m_camera->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(0, 1, GL_TRUE, &App->m_camera->GetProjectionMatrix()[0][0]);

	
	//Enable texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glUniform1i(glGetUniformLocation(m_program, "mytexture"), 0);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	
	
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	
	
}

void ModuleRenderExercise::CreateFrustum()
{
	float AspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
	m_frustum = new Frustum();
	m_frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
	m_frustum->SetViewPlaneDistances(0.1f, 100.0f);
	m_frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f , AspectRatio);
	m_frustum->SetPos(float3(0.0f, 4.0f, 8.0f));
	m_frustum->SetFront(-float3::unitZ);
	m_frustum->SetUp(float3::unitY);
	m_proj = m_frustum->ProjectionMatrix();
	m_view = m_frustum->ViewMatrix();
}
