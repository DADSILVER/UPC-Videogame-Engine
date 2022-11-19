#pragma once
#include "Module.h"
class ModuleTimer :
    public Module
{
public:
	bool Init();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	float GetDeltaTime();

private:
	float m_LastDeltaTime;

};

