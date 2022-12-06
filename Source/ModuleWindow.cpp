#include "Globals.h"
#include "Application.h"

#include "ModuleWindow.h"
#include "ModuleEditor.h"
#include "ModuleCamera.h"

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
		//Create window
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(0, &dm);
		m_MaxWidth = dm.w;
		m_MaxHeight = dm.h;
		m_Width = SCREEN_WIDTH;
		m_Height = SCREEN_HEIGHT;

	
		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		if(FULLSCREENINIT == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		m_Window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height, flags);

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
	//Destroy window
	if(m_Window != NULL)
	{
		SDL_DestroyWindow(m_Window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}


void ModuleWindow::WindowResized(int InWidth, int InHeight)
{
	m_Width = InWidth;
	m_Height = InHeight;
	App->m_Camera->ResizeWindow(m_Width, m_Height);
}

void ModuleWindow::SetTypeScreen(type_screen InTypeScreen)
{
	
	switch (InTypeScreen)
	{
	case FULLSCREEN:
		SDL_SetWindowFullscreen(m_Window, SDL_TRUE);
		SDL_SetWindowBordered(m_Window, SDL_FALSE);
		SDL_SetWindowResizable(m_Window, SDL_FALSE);
		break;
	case RESIZABLE:
		SDL_SetWindowResizable(m_Window, SDL_TRUE);
		SDL_SetWindowFullscreen(m_Window, SDL_FALSE);
		SDL_SetWindowBordered(m_Window, SDL_FALSE);
		break;
	case BORDERLESS:
		SDL_SetWindowBordered(m_Window, SDL_TRUE);
		SDL_SetWindowFullscreen(m_Window, SDL_FALSE);
		SDL_SetWindowResizable(m_Window, SDL_FALSE);
		break;
	}

	m_ActualTypeScreen = InTypeScreen;
}

float ModuleWindow::GetBrightness()
{
	return SDL_GetWindowBrightness(m_Window);
}

void ModuleWindow::SetBrightness(float& InBrightness)
{
	SDL_SetWindowBrightness(m_Window, InBrightness);
}

void ModuleWindow::SetWidth(int& InWidth)
{
	m_Width = InWidth;
	SDL_SetWindowSize(App->m_Window->m_Window, m_Width, m_Height);
}

void ModuleWindow::SetHeight(int& InHeight)
{
	m_Height = InHeight;
	SDL_SetWindowSize(App->m_Window->m_Window, m_Width, m_Height);
}
