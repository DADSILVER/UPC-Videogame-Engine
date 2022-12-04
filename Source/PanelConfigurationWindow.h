#pragma once
#include "Panel.h"

class PanelConfigurationWindow :
    public Panel
{
public:
    PanelConfigurationWindow(const char* InTitle);
    bool Draw() override;
};

