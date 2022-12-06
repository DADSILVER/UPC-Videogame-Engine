#pragma once
#include "Panel.h"
#include <dxgi1_4.h>

class PanelConfigurationWindow :
    public Panel
{
public:
    PanelConfigurationWindow(const char* InTitle);
    bool Draw() override;
   
};

