#pragma once
#include "Module.h"
#include "Geometry/Frustum.h"

class ModuleCamera :
    public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void SetFOV(float _horizontalFov);
	void SetAspectRatio(float _width, float _heigth);
	void SetPlaneDistances(float _near, float _far);
	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();
	void MoveCamera(moves_camera _move);

	void ResizeWindow(float _width, float _heigth);

private:

	float m_aspectRatio;

	Frustum* m_frustum;
};

