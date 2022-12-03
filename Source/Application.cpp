#pragma once
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleProgram.h"
#include "ModuleRenderExercise.h"
#include "ModuleDebugDraw.h"
#include "ModuleCamera.h"
#include "ModuleTimer.h"
#include "ModuleTexture.h"
#include "ModuleEditor.h"

using namespace std;

Application::Application()
{
	// Order matters: they will Init/start/update in this order
	m_modules.push_back(m_Window = new ModuleWindow());
	m_modules.push_back(m_Timer = new ModuleTimer());
	m_modules.push_back(m_Editor = new ModuleEditor());
	m_modules.push_back(m_Input = new ModuleInput());
	m_modules.push_back(m_Camera = new ModuleCamera());
	m_modules.push_back(m_Program = new ModuleProgram());
	m_modules.push_back(m_Texture = new ModuleTexture());
	m_modules.push_back(m_DebugDraw = new ModuleDebugDraw());
	m_modules.push_back(m_RendererExercise = new ModuleRenderExercise());
	m_modules.push_back(m_Renderer = new ModuleRender());
	
}

Application::~Application()
{
	for(list<Module*>::iterator it = m_modules.begin(); it != m_modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
	bool ret = true;

	for(list<Module*>::iterator it = m_modules.begin(); it != m_modules.end() && ret; ++it)
		ret = (*it)->Init();

	return ret;
}

bool Application::Start()
{
	bool ret = true;

	for (list<Module*>::iterator it = m_modules.begin(); it != m_modules.end() && ret; ++it)
		ret = (*it)->Start();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(list<Module*>::iterator it = m_modules.begin(); it != m_modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PreUpdate();

	for(list<Module*>::iterator it = m_modules.begin(); it != m_modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->Update();

	for(list<Module*>::iterator it = m_modules.begin(); it != m_modules.end() && ret == UPDATE_CONTINUE; ++it)
		ret = (*it)->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(list<Module*>::reverse_iterator it = m_modules.rbegin(); it != m_modules.rend() && ret; ++it)
		ret = (*it)->CleanUp();

	return ret;
}
