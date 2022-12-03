#include "ModuleCamera.h"
#include "Math/float3x3.h"
#include "Math/float3.h"
#include "Math/float2.h"
#include "Math/Quat.h"

#include <SDL_scancode.h>
#include <SDL_mouse.h>
#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTimer.h"

#include "Model.h"

ModuleCamera::ModuleCamera()
{
	m_aspectRatio = 0;
	m_MoveDist = 0.6f;
	m_RotateDegrees = 1.05f;
	m_VelocityMult = 1.0f;
	m_AngelY = 0;
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	m_aspectRatio = float(SCREEN_WIDTH) / float(SCREEN_HEIGHT);
	m_frustum = new Frustum();
	m_frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
	m_frustum->SetViewPlaneDistances(0.1f, 1000.0f);
	m_frustum->SetHorizontalFovAndAspectRatio(DEGTORAD * 90.0f, m_aspectRatio);
	m_frustum->SetPos(float3(0.0f, 2.0f, 8.0f));
	m_frustum->SetFront(-float3::unitZ);
	m_frustum->SetUp(float3::unitY);

    return true;
}

update_status ModuleCamera::PreUpdate()
{
    return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
	//TODO: Improve
	GetInputMove();
	if(m_Zoom)
	{
		SetFOV(DEGTORAD * 30.0f);
	}
	else
	{
		SetFOV(DEGTORAD * 90.0f);
	}
    return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
    return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
	delete m_frustum;
    return true;
}

void ModuleCamera::SetFOV(const float& InHorizontalFov)
{
	m_frustum->SetHorizontalFovAndAspectRatio(InHorizontalFov, m_aspectRatio);
}

void ModuleCamera::SetAspectRatio(const float& InWidth, const float& InHeigth)
{
	m_aspectRatio = InWidth / InHeigth;
}

void ModuleCamera::SetPlaneDistances(const float& InNear, const float& InFar)
{
		m_frustum->SetViewPlaneDistances(InNear, InFar);
}

void ModuleCamera::SetPosition(const float3& InPos)
{
	m_frustum->SetPos(InPos);
}

float4x4 ModuleCamera::GetProjectionMatrix() const
{
	return m_frustum->ProjectionMatrix();
}

float4x4 ModuleCamera::GetViewMatrix() const
{
	return m_frustum->ViewMatrix();
}

void ModuleCamera::MoveCamera(moves_camera InMove)
{
	switch (InMove)
	{
	case MOVE_STRAIGHT:
		m_frustum->SetPos(m_frustum->Pos() + (m_frustum->Front().Normalized() * m_MoveDist * App->m_Timer->GetDeltaTime()));
		break;
	case MOVE_BACK:
		m_frustum->SetPos(m_frustum->Pos() - (m_frustum->Front().Normalized() * m_MoveDist * App->m_Timer->GetDeltaTime()));
		break;
	case MOVE_RIGTH:
		m_frustum->SetPos(m_frustum->Pos() + (m_frustum->WorldRight().Normalized() * m_MoveDist * App->m_Timer->GetDeltaTime()));
		break;
	case MOVE_LEFT:
		m_frustum->SetPos(m_frustum->Pos() - (m_frustum->WorldRight().Normalized() * m_MoveDist * App->m_Timer->GetDeltaTime()));
		break;
	case ROTATE_UP:		
		Rotate(0, m_RotateDegrees * DEGTORAD * App->m_Timer->GetDeltaTime());
		break;
	case ROTATE_DOWN:
		
		Rotate(0, -m_RotateDegrees * DEGTORAD * App->m_Timer->GetDeltaTime());
		break;
	case ROTATE_RIGHT:
		Rotate(-m_RotateDegrees * DEGTORAD * App->m_Timer->GetDeltaTime(), 0);
		break;
	case ROTATE_LEFT:
		Rotate(m_RotateDegrees * DEGTORAD * App->m_Timer->GetDeltaTime(), 0);
		break;
	case ROTATE_FREE:
		float2 motion = App->m_Input->GetMouseMotion();
		Rotate(motion.y * 10 * DEGTORAD * App->m_Timer->GetDeltaTime(), motion.x * 10 * DEGTORAD * App->m_Timer->GetDeltaTime());

		break;
	}
	
}

void ModuleCamera::Rotate(const float& InPitch, const float& InYaw)
{
	// TODO : change to quat

	
	if ((float3x3::RotateAxisAngle(m_frustum->WorldRight(), InYaw) * m_frustum->Front().Normalized()).y > 0.96f
		|| (float3x3::RotateAxisAngle(m_frustum->WorldRight(), InYaw) * m_frustum->Front().Normalized()).y < -0.96f)
	{
		InYaw = 0;
	}
	
	m_frustum->SetFront(float3x3::RotateAxisAngle(m_frustum->WorldRight(), InYaw) * m_frustum->Front().Normalized());
	m_frustum->SetUp(float3x3::RotateAxisAngle(m_frustum->WorldRight(), InYaw) * m_frustum->Up().Normalized());

	m_frustum->SetFront(float3x3::RotateY(InPitch) * m_frustum->Front().Normalized());
	m_frustum->SetUp(float3x3::RotateY(InPitch) * m_frustum->Up().Normalized());

	//m_frustum->Transform(Quat::RotateY(InYaw)); 
	//m_frustum->SetUp(Quat(m_frustum->Up(), InPitch).Transform(m_frustum->Up().Normalized()));
	//m_frustum->Transform();
	//m_frustum->SetFront(m_frustum->Front(Quat::RotateAxisAngle(m_frustum->WorldRight(), InPitch).Transform(m_frustum->Front().Normalized())));
}

void ModuleCamera::OrbitAround()
{
	float2 motion = App->m_Input->GetMouseMotion();
	
	// Get orbit point (object transform)
	float3 direction = m_frustum->Pos() - App->m_Renderer->GetModel().GetCenterOfModel();

	// Rotate it
	direction = Quat(m_frustum->Up(), motion.y * 10 * DEGTORAD * App->m_Timer->GetDeltaTime()).Transform(direction);
	direction = Quat(m_frustum->WorldRight(), motion.x * 10 * DEGTORAD * App->m_Timer->GetDeltaTime()).Transform(direction);

	float3 directionNormalize = direction;
	directionNormalize.Normalize();

	if (directionNormalize.y <= 0.96f
		&& directionNormalize.y >= -0.96f)
	{
		// Set camera to where the rotated vector points from its starting position
		m_frustum->SetPos(direction + App->m_Renderer->GetModel().GetCenterOfModel());

		// Rotate camera to the orbit center
		LookAt(App->m_Renderer->GetModel().GetCenterOfModel());
	}

	
}

void ModuleCamera::LookAt(const float3& InLookAt)
{
	vec direction = InLookAt - m_frustum->Pos();

	direction.Normalize();
	vec up = vec::unitY;

	// Special case for when looking straight up
	if (direction.Cross(up).IsZero())
	{
		up = vec::unitZ;
	}
	vec oldFrom = m_frustum->Front().Normalized();
	vec oldUp = m_frustum->Up().Normalized();
	m_frustum->SetFront(float3x3::LookAt(oldFrom, direction, oldUp,up) * oldFrom);
	m_frustum->SetUp(float3x3::LookAt(oldFrom, direction, oldUp, up) * oldUp);
}

void ModuleCamera::GetInputMove() 
{
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_W))
	{
		MoveCamera(MOVE_STRAIGHT);
	}
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_R))
	{
		m_Zoom = true;
	}
	else
	{
		m_Zoom = false;
	}
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_F))
	{
		LookAt(App->m_Renderer->GetModel().GetCenterOfModel());
	}
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_S))
	{
		MoveCamera(MOVE_BACK);
	}
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_D))
	{
		MoveCamera(MOVE_RIGTH);
	}
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_A))
	{
		MoveCamera(MOVE_LEFT);
	}
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_UP))
	{
		MoveCamera(ROTATE_UP);
	}
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_DOWN))
	{
		MoveCamera(ROTATE_DOWN);
	}
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_RIGHT))
	{
		MoveCamera(ROTATE_RIGHT);
	}
	if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_LEFT))
	{
		MoveCamera(ROTATE_LEFT);
	}
	if (App->m_Input->GetMouseButton(SDL_BUTTON_RIGHT - 1))
	{
		
		if (App->m_Input->GetKeyboardButton(SDL_SCANCODE_LALT)) 
		{
			OrbitAround();
		}
		else
		{
			MoveCamera(ROTATE_FREE);
		}
	}
}

void ModuleCamera::ResizeWindow(const float& InWidth, const float& InHeigth)
{
	m_frustum->SetHorizontalFovAndAspectRatio(m_frustum->HorizontalFov(), InWidth / InHeigth);
}




