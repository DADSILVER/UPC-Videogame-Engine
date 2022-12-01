#pragma once

#include<list>
#include "Globals.h"
//#include "Module.h"

class Module;
class ModuleRender;
class ModuleWindow;
class ModuleProgram;
class ModuleInput;
class ModuleRenderExercise;
class ModuleDebugDraw;
class ModuleCamera;
class ModuleTimer;
class ModuleTexture;
class ModuleEditor;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* m_Renderer = nullptr;
	ModuleWindow* m_Window = nullptr;
	ModuleInput* m_Input = nullptr;
	ModuleProgram* m_Program = nullptr;
	ModuleRenderExercise* m_RendererExercise = nullptr;
	ModuleDebugDraw* m_DebugDraw = nullptr;
	ModuleCamera* m_Camera = nullptr;
	ModuleTimer* m_Timer = nullptr;
	ModuleTexture* m_Texture = nullptr;
	ModuleEditor* m_Editor = nullptr;

private:

	std::list<Module*> m_modules;

};

extern Application* App;
