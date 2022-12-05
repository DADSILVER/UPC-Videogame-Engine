#include "PanelConsole.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>


static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

//static int Console::TextEditCallbackStub(ImGuiInputTextCallbackData* data)
//{
//    Console* console = (console*)data->UserData;
//    return console->TextEditCallback(data);
//}


PanelConsole::PanelConsole(const char* InTitle) : Panel(InTitle)
{
    AutoScroll = true;
    ScrollToBottom = false;
    AddLog("Welcome to Dear ImGui!");
}

void PanelConsole::ClearLog()
{
    for (int i = 0; i < Items.Size; i++)
        free(Items[i]);
    Items.clear();
}

void PanelConsole::AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
    // FIXME-OPT
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf) - 1] = 0;
    va_end(args);
    Items.push_back(Strdup(buf));
    ScrollToBottom = true;
}


bool PanelConsole::Draw()
{
	
    if (!m_Open)
    {
        return true;
    }
    ImGui::SetNextWindowSize(ImVec2(1200, 200), 0); //ImGuiCond_FirstUseEver
	ImGui::Begin(m_Title, &m_Open);

    // Options menu
    if (ImGui::BeginPopup("Options"))
    {
        ImGui::Checkbox("Auto-scroll", &AutoScroll);
        ImGui::EndPopup();
    }

    // Options, Filter
    if (ImGui::Button("Options"))
        ImGui::OpenPopup("Options");
    ImGui::SameLine();
    Filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
    ImGui::Separator();

    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    bool copy_to_clipboard = ImGui::Button("Copy");
    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, -5), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear")) ClearLog();
            ImGui::EndPopup();
        }
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
        if (copy_to_clipboard)
            ImGui::LogToClipboard();
        for (int i = 0; i < Items.Size; i++)
        {
            const char* item = Items[i];
            if (!Filter.PassFilter(item))
                continue;

            // Normally you would store more information in your item than just a string.
            // (e.g. make Items[] an array of structure, store color/type etc.)
            ImVec4 color;
            bool has_color = false;
            if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
            else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
            if (has_color)
                ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::TextUnformatted(item);
            if (has_color)
                ImGui::PopStyleColor();
        }
        if (copy_to_clipboard)
            ImGui::LogFinish();

        if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        ScrollToBottom = false;

       ImGui::PopStyleVar();
    }
    ImGui::EndChild();
	ImGui::End();

    return true;
}


