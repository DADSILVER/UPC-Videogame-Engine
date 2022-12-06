#include "ModuleTimer.h"
#include "Time/Clock.h"
#include "Globals.h"

bool ModuleTimer::Init()
{
    return true;
}

bool ModuleTimer::Start()
{
    m_LastDeltaTime = float(Clock::Time());
    return true;
}

update_status ModuleTimer::PreUpdate()
{
    m_Milisecond = float(Clock::Time() - m_LastDeltaTime);

    m_DeltaTime = m_Milisecond / 1000.0f;
    if (m_DeltaTime < LOW_LIMIT) {
        m_DeltaTime = LOW_LIMIT;
    }
    else if (m_DeltaTime > HIGH_LIMIT) {
        m_DeltaTime = HIGH_LIMIT;
    }

    m_LastDeltaTime = float(Clock::Time());
    return UPDATE_CONTINUE;
}

update_status ModuleTimer::Update()
{
    return UPDATE_CONTINUE;
}

bool ModuleTimer::CleanUp()
{
    return true;
}

