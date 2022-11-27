#pragma once
#include "Module.h"
#include "Geometry/Frustum.h"
#include "Math/float3.h"

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
	void GetInputMove();
	void ResizeWindow(float _width, float _heigth);

	

private:
	void MoveCamera(moves_camera _move);
	void LookAt(float3 inLookUp);
	void OrbitAround();
	float lenght2(vec inDirection);

private:

	bool m_Zoom;

	Frustum* m_frustum;

	float m_aspectRatio;
	float m_MoveDist;
	float m_RotateDegrees;
	float m_VelocityMult;
	float m_DistanceToObject;
	float m_AngelY;
};

