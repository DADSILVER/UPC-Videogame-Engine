#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		engLOG("Dummy Init!");
		return true;
	}

	bool CleanUp()
	{
		engLOG("Dummy CleanUp!");
		return true;
	}
};