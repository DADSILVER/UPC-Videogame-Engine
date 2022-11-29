#pragma once
#include "Module.h"
#include "Geometry/Frustum.h"

class Model;

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

	void RenderTriangle();

	void CreateFrustum();

	Model GetModel();

private:

	int m_win_width, m_win_height, m_program;
	unsigned m_vbo;
	unsigned m_vao;
	unsigned m_ebo;
	unsigned m_Texture;

	Frustum* m_frustum;

	float4x4 m_model;
	float4x4 m_proj;
	float4x4 m_view;

	Model* m_BakerHause;
	Model* m_NotTextureModel;
};

