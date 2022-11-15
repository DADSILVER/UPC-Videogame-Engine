#pragma once
#include "Module.h"
#include "Globals.h"
#include "SDL_scancode.h"

typedef unsigned __int8 Uint8;

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
	bool CleanUp();

private:
	const Uint8 *keyboard = NULL;
	KeyState m_keyboard[SDL_NUM_SCANCODES] = { KS_IDLE };
	KeyState m_mouse_buttons[5] = { KS_IDLE };
};