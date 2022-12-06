#pragma once
#include "Module.h"

#include "Globals.h"
#include "Geometry/Frustum.h"

#include "Model.h"


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
	void WindowResized(float InWidth, float InHeight);

	inline Model GetModel() {return *m_Model;}

	void LoadModel(const char* InFileName);

public:
	void* m_Context;
	int m_Program;

private:

	int m_win_width, m_win_height;

	Model* m_Model;
};
