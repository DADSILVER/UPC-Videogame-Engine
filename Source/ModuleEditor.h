#pragma once
#include "Module.h"
#include <imgui.h>
class ModuleEditor :
	public Module
{
public:
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);

private:
	ImGuiIO m_io;
	ImVec4 m_clear_color;
	bool show_demo_window = true;
	bool show_another_window = false;
	void* m_context;
};
