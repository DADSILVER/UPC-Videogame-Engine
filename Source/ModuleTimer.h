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

	inline const float GetDeltaTime() const { return m_DeltaTime; }
	inline const float GetMiliseconds() const { return m_Milisecond; }

private:
	float m_LastDeltaTime = 0;
	float m_DeltaTime;
	float m_Milisecond;

};

