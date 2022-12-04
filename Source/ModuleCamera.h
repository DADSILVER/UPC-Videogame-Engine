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

	void SetFOV(const float& InhorizontalFov);
	void SetPlaneDistances(const float& Innear, const float& Infar);
	void SetPosition(const float3& InPos);

	float4x4 GetProjectionMatrix() const;
	float4x4 GetViewMatrix() const;

	void GetInputMove();
	void ResizeWindow(const float& Inwidth, const float& Inheigth);
	void LookAt(const float3& InLookUp);
	

private:
	void MoveCamera(moves_camera _move);
	void Rotate(const float& InPitch, float InYaw);
	void OrbitAround();

	bool CanSetPos(const float InPos) {return InPos <= 0.99f && InPos >= -0.99f;}

private:

	bool m_Zoom;

	Frustum* m_frustum;

	float m_MoveDist;
	float m_RotateDegrees;
};

