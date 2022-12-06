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
	

	inline Model GetModel() { return *m_Model; }


	void LoadModel(const char* InFileName);

	

public:
	void* m_Context;
	int m_Program;
	float3 M_BackGroundColor{ 1, 1, 1 };
	float3 m_GridColor{ 0, 0, 0 };

private:

	Model* m_Model;
};
