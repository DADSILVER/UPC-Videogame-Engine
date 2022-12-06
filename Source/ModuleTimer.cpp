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
    m_LastDeltaTime = float (Clock::Time());
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


const float ModuleTimer::GetDeltaTime() const
{
    float OutDeltaTime = float(Clock::Time() - m_LastDeltaTime) / 1000.0f;
    if (OutDeltaTime < LOW_LIMIT) {
        OutDeltaTime = LOW_LIMIT;
    }
    else if (OutDeltaTime > HIGH_LIMIT) {
        OutDeltaTime = HIGH_LIMIT;
    }
    return OutDeltaTime;
}
