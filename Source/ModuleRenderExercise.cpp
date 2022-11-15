#include "ModuleRenderExercise.h"
#include "Globals.h"
#include "SDL.h"
#include "libs/glew-2.1.0/include/GL/glew.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "Geometry/Frustum.h"
#include "Math/MathAll.h"
#include "Application.h"

ModuleRenderExercise::ModuleRenderExercise()
{
	m_model = float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f),
		float4x4::RotateZ(pi / 4.0f),
		//float4x4::identity,
		float3(2.0f, 1.0f, 1.0f));
	//m_model.Transpose();
	//m_view = float4x4::LookAt(float3(0.0f, 4.0f, 8.0f), float3(0.0f, 0.0f, 0.0f), -float3::unitZ , float3::unitY, float3::unitY);
}

bool ModuleRenderExercise::Init()
{
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
	//RenderVBO();
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
	DestroyVBO();
	delete m_frustum;
	return true;
}

// This function must be called one time at creation of vertex buffer
void ModuleRenderExercise::CreateTriangleVBO()
{
	float m_vtx_data[] = { -1.0f, -1.0f, 0.0f, 
							1.0f, -1.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 
							-1.0f, -1.0f, 0.0f,
							0.0f, -2.0f, 0.0f,
							1.0f, -1.0f, 0.0f 
	};
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // set vbo active
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vtx_data), m_vtx_data, GL_STATIC_DRAW);
}

void ModuleRenderExercise::DestroyVBO()
{
	glDeleteBuffers(1, &m_vbo);
}

// This function must be called each frame for drawing the triangle
void ModuleRenderExercise::RenderVBO()
{
}

void ModuleRenderExercise::RenderTriangle()
{

	glUseProgram(m_program);
	glUniformMatrix4fv(2, 1, GL_TRUE, &m_model[0][0]);
	glUniformMatrix4fv(1, 1, GL_TRUE, &App->m_camera->GetViewMatrix()[0][0]);
	glUniformMatrix4fv(0, 1, GL_TRUE, &App->m_camera->GetProjectionMatrix()[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(0);
	// size = 3 float per vertex
	// stride = 0 is equivalent to stride = sizeof(float)*3
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
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
