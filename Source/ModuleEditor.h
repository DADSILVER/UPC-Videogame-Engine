#pragma once
#include "Module.h"
#include <imgui.h>
#include <vector>
#include <list>

#include "Console.h"
#include "Panel.h"

class ModuleEditor :
	public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void NewTestImgUI();

	void NewHelloWorld();

	const std::vector<float>& GetFps() const {return m_Fps;}

private:
	ImGuiIO m_io;
	ImVec4 m_clear_color;

	bool show_demo_window = true;
	bool show_another_window = false;
	void* m_context;

	std::vector<float> m_Fps;

	std::list<Panel*> m_Panels;

public:
	Console m_console;
};
