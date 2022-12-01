#include "ModuleRender.h"

#include "Model.h"

#include "Globals.h"
#include "Application.h"

#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleProgram.h"


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
	
	App->m_Editor->m_console.AddLog(engLOG("Creating Renderer context"));
	App->m_renderer->context = SDL_GL_CreateContext(App->m_window->window);
	SDL_GL_MakeCurrent(App->m_window->window, App->m_renderer->context);

	

	GLenum err = glewInit();
	// … check for errors
	App->m_Editor->m_console.AddLog(engLOG("Using Glew %s", glewGetString(GLEW_VERSION)));
	// Should be 2.0

	App->m_Editor->m_console.AddLog(engLOG("Vendor: %s", glGetString(GL_VENDOR)));
	App->m_Editor->m_console.AddLog(engLOG("Renderer: %s", glGetString(GL_RENDERER)));
	App->m_Editor->m_console.AddLog(engLOG("OpenGL version supported %s", glGetString(GL_VERSION)));
	App->m_Editor->m_console.AddLog(engLOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION)));

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise


	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);



	//Load Model
	//Model* BakerHause = new Model();
	//BakerHause->Load("BakerHouse.fbx");

	m_program = App->m_program->CreateProgram();

	return true;
}

update_status ModuleRender::PreUpdate()
{
	
	SDL_GetWindowSize(App->m_window->window, &m_win_width, &m_win_height);
	glViewport(0, 0, m_win_width, m_win_height);
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	//SDL_GL_SwapWindow(App->m_window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	App->m_Editor->m_console.AddLog(engLOG("Destroying renderer"));
	SDL_GL_DeleteContext(context);

	//Destroy window

	return true;
}

void ModuleRender::WindowResized(unsigned _width, unsigned _height)
{
	App->m_camera->ResizeWindow(_width, _height);
}


