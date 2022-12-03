#pragma once

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

public:
	SDL_Window* m_Window = NULL;

	SDL_Surface* m_Screen_Surface = NULL;
};