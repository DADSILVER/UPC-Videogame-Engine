#include <stdlib.h>
#include "Application.h"

#include "ModuleRender.h"
#include "ModuleEditor.h"

#include "Panel.h"
#include "PanelConsole.h"

#include "Globals.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/lib/x64/SDL2.lib" )
#pragma comment( lib, "SDL/lib/x64/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,  
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = NULL;

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			
			App = new Application();
			App->m_Editor->m_Console->AddLog(engLOG("Application Creation --------------"));
			state = MAIN_START;
			break;

		case MAIN_START:

			App->m_Editor->m_Console->AddLog(engLOG("Application Init --------------"));
			if (App->Init() == false)
			{
				App->m_Editor->m_Console->AddLog(engLOG("Application Init exits with error -----"));
				state = MAIN_EXIT;
			}

			App->m_Editor->m_Console->AddLog(engLOG("Application Start --------------"));
			if (App->Start() == false)
			{
				App->m_Editor->m_Console->AddLog(engLOG("Application Start exits with error -----"));
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				App->m_Editor->m_Console->AddLog(engLOG("Application Update --------------"));
			}
			
			
			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			if (update_return == UPDATE_ERROR)
			{
				App->m_Editor->m_Console->AddLog(engLOG("Application Update exits with error -----"));
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			App->m_Editor->m_Console->AddLog(engLOG("Application CleanUp --------------"));
			if (App->CleanUp() == false)
			{
				engLOG("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}

	}

	engLOG("Bye :)\n");
	delete App;
	
	return main_return;
}
