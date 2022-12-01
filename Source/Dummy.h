#pragma once

#include "Globals.h"
#include "Application.h"

#include "Module.h"
#include "ModuleEditor.h"


class ModuleDummy : public Module
{
	bool Init()
	{
		App->m_Editor->m_console.AddLog(engLOG("Dummy Init!"));
		return true;
	}

	bool CleanUp()
	{
		App->m_Editor->m_console.AddLog(engLOG("Dummy CleanUp!"));
		return true;
	}
};