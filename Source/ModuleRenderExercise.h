#pragma once
#include "Module.h"
#include "Geometry/Frustum.h"

class ModuleRenderExercise :
    public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void CreateTriangleVBO();

	void DestroyVBO();

	void RenderVBO();

	void RenderTriangle();

	void CreateFrustum();

private:

	int m_win_width, m_win_height, m_program;
	unsigned m_vbo;
	Frustum* m_frustum;

	float4x4 m_model;
	float4x4 m_proj;
	float4x4 m_view;
};

