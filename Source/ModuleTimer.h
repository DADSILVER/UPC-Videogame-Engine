#pragma once
#include "Module.h"


class ModuleTimer :
    public Module
{
public:
	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	const float GetDeltaTime() const;

private:
	float m_LastDeltaTime;

};

