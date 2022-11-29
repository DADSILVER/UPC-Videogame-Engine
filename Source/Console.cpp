#include "Console.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

//static int Console::TextEditCallbackStub(ImGuiInputTextCallbackData* data)
//{
//    Console* console = (console*)data->UserData;
//    return console->TextEditCallback(data);
//}

void Console::Draw()
{
	ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
	ImGui::Begin("Console");


    // Command-line
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (ImGui::InputText("Input", m_InputBuf, IM_ARRAYSIZE(m_InputBuf), input_text_flags, NULL, NULL))
    {
        char* s = m_InputBuf;
        Strtrim(s);
        if (s[0])
            //ExecCommand(s);
        strcpy(s, "");
        reclaim_focus = true;
    }


	ImGui::End();
}


