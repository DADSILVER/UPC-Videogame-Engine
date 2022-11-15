#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleProgram;
class ModuleInput;
class ModuleRenderExercise;
class ModuleDebugDraw;
class ModuleCamera;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* m_renderer = nullptr;
	ModuleWindow* m_window = nullptr;
	ModuleInput* m_input = nullptr;
	ModuleProgram* m_program = nullptr;
	ModuleRenderExercise* m_rendererExercise = nullptr;
	ModuleDebugDraw* m_debugDraw = nullptr;
	ModuleCamera* m_camera = nullptr;

private:

	std::list<Module*> modules;

};

extern Application* App;
