#include "Globals.h"
#include "Application.h"

#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"

#include "SDL/include/SDL.h"
#include "imgui_impl_sdl.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	App->m_Editor->m_console.AddLog(engLOG("Init SDL input event system"));
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		App->m_Editor->m_console.AddLog(engLOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError()));
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
    
	m_MouseMotion = { 0, 0 };

    while (SDL_PollEvent(&m_sdlEvent) != 0)
    {
		ImGui_ImplSDL2_ProcessEvent(&m_sdlEvent);

        switch (m_sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
                if (m_sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || m_sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    App->m_Renderer->WindowResized(m_sdlEvent.window.data1, m_sdlEvent.window.data2);
                break;
			case SDL_KEYDOWN:
				m_keyboard[m_sdlEvent.key.keysym.scancode] = KS_DOWN;
				break;

			case SDL_KEYUP:
				m_keyboard[m_sdlEvent.key.keysym.scancode] = KS_IDLE;
				break;

			case SDL_MOUSEBUTTONDOWN:
				m_mouseButtons[m_sdlEvent.button.button - 1] = KS_DOWN;
				break;
			case SDL_MOUSEMOTION:
				m_MouseMotion.x = (float)-m_sdlEvent.motion.yrel;
				m_MouseMotion.y = (float)-m_sdlEvent.motion.xrel;
				break;
			case SDL_MOUSEBUTTONUP:
				m_mouseButtons[m_sdlEvent.button.button - 1] = KS_IDLE;
				break;
			case SDL_DROPFILE:
				App->m_Renderer->LoadModel(m_sdlEvent.drop.file);
				break;
        }


    }

    return UPDATE_CONTINUE;
}

const bool& ModuleInput::GetKeyboardButton(int InScancode) {
	return m_keyboard[InScancode];
}

const bool& ModuleInput::GetMouseButton(int InScancode) {
	return m_mouseButtons[InScancode];
}

float2 ModuleInput::GetMouseMotion() {
	return m_MouseMotion;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	App->m_Editor->m_console.AddLog(engLOG("Quitting SDL input event subsystem"));
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
