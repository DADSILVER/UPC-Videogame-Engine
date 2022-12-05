#pragma once
#include "Panel.h"
class PanelAbout :
    public Panel
{
public:

	PanelAbout(const char* InTitle);

	bool Draw() override;
};

