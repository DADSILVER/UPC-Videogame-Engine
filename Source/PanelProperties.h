#pragma once
#include "Panel.h"
class PanelProperties :
    public Panel
{

public:
    PanelProperties(const char* InTitle);

    bool Draw();
};

