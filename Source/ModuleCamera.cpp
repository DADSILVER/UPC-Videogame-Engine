#include "ModuleCamera.h"
#include "Math/float3x3.h"
#include <SDL_scancode.h>
#include <SDL_mouse.h>
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleTimer.h"

ModuleCamera::ModuleCamera()
{
	m_aspectRatio = 0;
	m_MoveDist = 0.6f;
	m_RotateDegrees = 1.05f;
	m_VelocityMult = 1.0f;
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	m_aspectRatio = float(SCREEN_WIDTH) / float(SCREEN_HEIGHT);
	m_frustum = new Frustum();
	m_frustum->SetKind(FrustumSpaceGL, FrustumRightHanded);
	m_frustum->SetViewPlaneDistances(0.1f, 100.0f);
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

void ModuleCamera::SetFOV(float _horizontalFov)
{
	m_frustum->SetHorizontalFovAndAspectRatio(_horizontalFov, m_aspectRatio);
}

void ModuleCamera::SetAspectRatio(float _width, float _heigth)
{
	m_aspectRatio = _width / _heigth;
}

void ModuleCamera::SetPlaneDistances(float _near, float _far)
{
		m_frustum->SetViewPlaneDistances(_near, _far);
}

float4x4 ModuleCamera::GetProjectionMatrix()
{
	return m_frustum->ProjectionMatrix();
}

float4x4 ModuleCamera::GetViewMatrix()
{
	return m_frustum->ViewMatrix();
}

void ModuleCamera::MoveCamera(moves_camera _move)
{
	switch (_move)
	{
	case MOVE_STRAIGHT:
		m_frustum->SetPos(m_frustum->Pos() + (m_frustum->Front().Normalized() * m_MoveDist * App->m_timer->GetDeltaTime()));
		break;
	case MOVE_BACK:
		m_frustum->SetPos(m_frustum->Pos() - (m_frustum->Front().Normalized() * m_MoveDist * App->m_timer->GetDeltaTime()));
		break;
	case MOVE_RIGTH:
		m_frustum->SetPos(m_frustum->Pos() + (m_frustum->WorldRight().Normalized() * m_MoveDist * App->m_timer->GetDeltaTime()));
		break;
	case MOVE_LEFT:
		m_frustum->SetPos(m_frustum->Pos() - (m_frustum->WorldRight().Normalized() * m_MoveDist * App->m_timer->GetDeltaTime()));
		break;
	case ROTATE_UP:
		m_frustum->SetFront(float3x3::RotateAxisAngle(m_frustum->WorldRight() , m_RotateDegrees  * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Front().Normalized());
		m_frustum->SetUp(float3x3::RotateAxisAngle(m_frustum->WorldRight(), m_RotateDegrees  * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Up().Normalized());
		break;
	case ROTATE_DOWN:
		m_frustum->SetFront(float3x3::RotateAxisAngle(m_frustum->WorldRight(), -m_RotateDegrees  * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Front().Normalized() );
		m_frustum->SetUp(float3x3::RotateAxisAngle(m_frustum->WorldRight(), -m_RotateDegrees  * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Up().Normalized() );
		break;
	case ROTATE_RIGHT:
		m_frustum->SetFront(float3x3::RotateY(-m_RotateDegrees * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Front().Normalized());
		m_frustum->SetUp(float3x3::RotateY(-m_RotateDegrees * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Up().Normalized());
		break;
	case ROTATE_LEFT:
		m_frustum->SetFront(float3x3::RotateY(m_RotateDegrees * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Front().Normalized());
		m_frustum->SetUp(float3x3::RotateY(m_RotateDegrees * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Up().Normalized());
		m_frustum->WorldRight();
		break;
	case ROTATE_FREE:
		float2 motion = App->m_input->GetMouseMotion();
		m_frustum->SetFront(float3x3::RotateAxisAngle(m_frustum->WorldRight(), motion.x * 10 * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Front().Normalized());
		m_frustum->SetUp(float3x3::RotateAxisAngle(m_frustum->WorldRight(), motion.x * 10 * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Up().Normalized());

		m_frustum->SetFront(float3x3::RotateY(motion.y * 10 * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Front().Normalized());
		m_frustum->SetUp(float3x3::RotateY(motion.y * 10 * DEGTORAD * App->m_timer->GetDeltaTime()) * m_frustum->Up().Normalized());
		m_frustum->WorldRight();
		break;
	}
}

void ModuleCamera::GetInputMove() 
{
	if (App->m_input->GetKeyboardButton(SDL_SCANCODE_W))
	{
		MoveCamera(MOVE_STRAIGHT);
	}
	if (App->m_input->GetKeyboardButton(SDL_SCANCODE_R))
	{
		m_Zoom = true;
	}
	else
	{
		m_Zoom = false;
	}
	if (App->m_input->GetKeyboardButton(SDL_SCANCODE_S))
	{
		MoveCamera(MOVE_BACK);
	}
	if (App->m_input->GetKeyboardButton(SDL_SCANCODE_D))
	{
		MoveCamera(MOVE_RIGTH);
	}
	if (App->m_input->GetKeyboardButton(SDL_SCANCODE_A))
	{
		MoveCamera(MOVE_LEFT);
	}
	if (App->m_input->GetKeyboardButton(SDL_SCANCODE_UP))
	{
		MoveCamera(ROTATE_UP);
	}
	if (App->m_input->GetKeyboardButton(SDL_SCANCODE_DOWN))
	{
		MoveCamera(ROTATE_DOWN);
	}
	if (App->m_input->GetKeyboardButton(SDL_SCANCODE_RIGHT))
	{
		MoveCamera(ROTATE_RIGHT);
	}
	if (App->m_input->GetKeyboardButton(SDL_SCANCODE_LEFT))
	{
		MoveCamera(ROTATE_LEFT);
	}
	if (App->m_input->GetMouseButton(SDL_BUTTON_RIGHT - 1))
	{
		MoveCamera(ROTATE_FREE);
	}
}

void ModuleCamera::ResizeWindow(float _width, float _heigth)
{
	//SetAspectRatio(_width, _heigth);
	m_frustum->SetHorizontalFovAndAspectRatio(m_frustum->HorizontalFov(), _width/ _heigth);
}
