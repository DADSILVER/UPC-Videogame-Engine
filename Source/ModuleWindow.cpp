#include "Globals.h"
#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleEditor.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	App->m_Editor->m_Console->AddLog(engLOG("Init SDL window & surface"));
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		App->m_Editor->m_Console->AddLog(engLOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError()));
		ret = false;
	}
	else
	{
		//Create window
		int width = SCREEN_WIDTH;
		int height = SCREEN_HEIGHT;
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		m_Window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(m_Window == NULL)
		{
			App->m_Editor->m_Console->AddLog(engLOG("Window could not be created! SDL_Error: %s\n", SDL_GetError()));
			ret = false;
		}
		else
		{
			//Get window surface
			
			m_Screen_Surface = SDL_GetWindowSurface(m_Window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	App->m_Editor->m_Console->AddLog(engLOG("Destroying SDL window and quitting all SDL systems"));

	//Destroy window
	if(m_Window != NULL)
	{
		SDL_DestroyWindow(m_Window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

