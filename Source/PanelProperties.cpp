#include "PanelProperties.h"

#include "imgui.h"


PanelProperties::PanelProperties(const char* InTitle) : Panel(InTitle)
{
}

bool PanelProperties::Draw()
{
	if (!m_Open)
	{
		return true;
	}
    return true;
}
