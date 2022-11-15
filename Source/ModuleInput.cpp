#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	engLOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		engLOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->m_renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                break;
			case SDL_KEYDOWN:
				m_keyboard[sdlEvent.key.keysym.scancode] = KS_DOWN;
				break;

			case SDL_KEYUP:
				m_keyboard[sdlEvent.key.keysym.scancode] = KS_IDLE;
				break;

			case SDL_MOUSEBUTTONDOWN:
				m_mouse_buttons[sdlEvent.button.button - 1] = KS_DOWN;
				break;

			case SDL_MOUSEBUTTONUP:
				m_mouse_buttons[sdlEvent.button.button - 1] = KS_IDLE;
				break;
        }
    }
	if (m_keyboard[SDL_SCANCODE_W]) 
	{
		App->m_renderer->MoveCamera(MOVE_STRAIGHT);
	}
	if (m_keyboard[SDL_SCANCODE_S])
	{
		App->m_renderer->MoveCamera(MOVE_BACK);
	}
	if (m_keyboard[SDL_SCANCODE_D])
	{
		App->m_renderer->MoveCamera(MOVE_RIGTH);
	}
	if (m_keyboard[SDL_SCANCODE_A])
	{
		App->m_renderer->MoveCamera(MOVE_LEFT);
	}
	if (m_keyboard[SDL_SCANCODE_UP])
	{
		App->m_renderer->MoveCamera(ROTATE_UP);
	}
	if (m_keyboard[SDL_SCANCODE_DOWN])
	{
		App->m_renderer->MoveCamera(ROTATE_DOWN);
	}
	if (m_keyboard[SDL_SCANCODE_RIGHT])
	{
		App->m_renderer->MoveCamera(ROTATE_RIGHT);
	}
	if (m_keyboard[SDL_SCANCODE_LEFT])
	{
		App->m_renderer->MoveCamera(ROTATE_LEFT);
	}
	if (m_keyboard[SDL_mo])
	{
		App->m_renderer->MoveCamera(ROTATE_LEFT);
	}




    keyboard = SDL_GetKeyboardState(NULL);

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	engLOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
