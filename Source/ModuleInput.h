#pragma once
#include "Module.h"

#include "SDL_scancode.h"

#include "Globals.h"
#include "SDL/include/SDL.h"

#include "Math/float2.h"



enum KeyState
{
	KS_IDLE = 0,
	KS_DOWN,
	KS_REPEAT,
	KS_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status Update();
	bool GetKeyboardButton(int InScancode);
	bool GetMouseButton(int InScancode);
	float2 GetMouseMotion();
	bool CleanUp();

private:
	SDL_Event m_sdlEvent;
	KeyState m_keyboard[SDL_NUM_SCANCODES] = { KS_IDLE };
	KeyState m_mouseButtons[5] = { KS_IDLE };
	float2 m_MouseMotion = { 0, 0 };
	float2 m_LastMouseMotion = { 0, 0 };
};