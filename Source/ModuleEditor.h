#pragma once
#include "Module.h"

#include <imgui.h>
#include <vector>
#include <list>

#include "Panel.h"
#include "PanelAbout.h"
#include "PanelConfigurationWindow.h"
#include "PanelConsole.h"
#include "PanelProperties.h"

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
	bool DrawMenu();

	const std::vector<float>& GetFps() const {return m_Fps;}
	const std::vector<float>& GetMs() const { return m_Ms; }

private:
	ImGuiIO m_io;
	ImVec4 m_clear_color;

	bool show_demo_window = true;
	bool show_another_window = false;
	//void* m_context;

	std::vector<float> m_Fps;
	std::vector<float> m_Ms;

	std::list<Panel*> m_Panels;

public:
	PanelConsole* m_Console;
	PanelAbout* m_About;
	PanelConfigurationWindow* m_ConfigWindow;
	PanelProperties* m_ConfigModel;
};
