#pragma once
#include "Module.h"
#include "Globals.h"
#include "Geometry/Frustum.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
//class Frustum;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);

public:
	void* context;
	int m_Program;

private:

	int m_win_width, m_win_height;
	unsigned m_vbo;
	unsigned m_vao;
	unsigned m_ebo;
	unsigned m_Texture;
	Frustum* m_frustum;
};
