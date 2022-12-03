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

	void SetFOV(float InhorizontalFov);
	void SetAspectRatio(float Inwidth, float Inheigth);
	void SetPlaneDistances(float Innear, float Infar);
	void SetPosition(float3 InPos);

	float4x4 GetProjectionMatrix() const;
	float4x4 GetViewMatrix() const;

	void GetInputMove();
	void ResizeWindow(float Inwidth, float Inheigth);
	void LookAt(float3 InLookUp);
	

private:
	void MoveCamera(moves_camera _move);
	void Rotate(float InPitch, float InYaw);	
	void OrbitAround();

private:

	bool m_Zoom;

	Frustum* m_frustum;

	float m_aspectRatio;
	float m_MoveDist;
	float m_RotateDegrees;
	float m_VelocityMult;
	float m_AngelY;
};

