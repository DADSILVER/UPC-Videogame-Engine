#include "ModuleRender.h"

#include "Model.h"

#include "Globals.h"
#include "Application.h"

#include "ModuleEditor.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleProgram.h"
#include "ModuleDebugDraw.h"

#include "SDL.h"
#include "libs/glew-2.1.0/include/GL/glew.h"

ModuleRender::ModuleRender()
{
	
}

// Destructor
ModuleRender::~ModuleRender()
{
}

// Called before render is available
bool ModuleRender::Init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits
	
	App->m_Editor->m_Console->AddLog(engLOG("Creating Renderer context"));
	App->m_Renderer->m_Context = SDL_GL_CreateContext(App->m_Window->m_Window);
	SDL_GL_MakeCurrent(App->m_Window->m_Window, App->m_Renderer->m_Context);
	SDL_GL_SetSwapInterval(0);
	

	GLenum err = glewInit();
	// � check for errors
	App->m_Editor->m_Console->AddLog(engLOG("Using Glew %s", glewGetString(GLEW_VERSION)));
	// Should be 2.0

	App->m_Editor->m_Console->AddLog(engLOG("Vendor: %s", glGetString(GL_VENDOR)));
	App->m_Editor->m_Console->AddLog(engLOG("Renderer: %s", glGetString(GL_RENDERER)));
	App->m_Editor->m_Console->AddLog(engLOG("OpenGL version supported %s", glGetString(GL_VERSION)));
	App->m_Editor->m_Console->AddLog(engLOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION)));

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise


	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);



	//Load Model BakerHouse
	m_Model = new Model();
	m_Model->Load("source/BakerHouse.fbx");
	//m_BakerHause->SetModelMatrix(
	//	float4x4::FromTRS(float3(10.0f, -10.0f, 0.0f),
	//		float4x4::RotateZ(0),
	//		//float3(0.01f, 0.01f, 0.01f)
	//		float3(1.0f, 1.0f, 1.0f)
	//	)
	//);

	m_Program = App->m_Program->CreateProgram();

	return true;
}

update_status ModuleRender::PreUpdate()
{
	
	SDL_GetWindowSize(App->m_Window->m_Window, &m_win_width, &m_win_height);
	glViewport(0, 0, m_win_width, m_win_height);
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_ESCAPE))
	{
		return UPDATE_STOP;
	}

	App->m_DebugDraw->Draw(App->m_Camera->GetViewMatrix(), App->m_Camera->GetProjectionMatrix(), SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Model->Draw();

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	//SDL_GL_SwapWindow(App->m_Window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	App->m_Editor->m_Console->AddLog(engLOG("Destroying renderer"));
	SDL_GL_DeleteContext(m_Context);
	glDeleteProgram(m_Program);
	delete m_Model;

	return true;
}

void ModuleRender::WindowResized(float InWidth, float InHeight)
{
	App->m_Camera->ResizeWindow(InWidth, InHeight);
}

void ModuleRender::LoadModel(const char* InFileName)
{
	delete m_Model;
	m_Model = new Model();
	m_Model->Load(InFileName);
	App->m_Camera->SetPosition(m_Model->GetInitVisionPos());
	App->m_Camera->LookAt(m_Model->GetCenterOfModel());
}


