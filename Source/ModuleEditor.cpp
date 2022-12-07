#include "ModuleEditor.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include <gl/GL.h>

#include "Application.h"
#include "PanelConsole.h"

#include "Panel.h"
#include "PanelConfigurationWindow.h"
#include "PanelProperties.h"
#include "PanelAbout.h"

#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTimer.h"

ModuleEditor::ModuleEditor()
{
    m_Panels.push_back(m_ConfigWindow = new PanelConfigurationWindow("Configuration"));
    m_Panels.push_back(m_Console = new PanelConsole("Console"));
    m_Panels.push_back(m_About = new PanelAbout("About"));
    m_Panels.push_back(m_ConfigModel = new PanelProperties("Model"));
    m_clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    m_io = ImGui::GetIO(); (void)m_io;
    m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    m_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    return true;
}

bool ModuleEditor::Start()
{
    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(App->m_Window->m_Window, App->m_Renderer->m_Context);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    return true;
}

update_status ModuleEditor::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->m_Window->m_Window);
    ImGui::NewFrame();

    if (m_Fps.size() >= 100) {
        m_Fps.erase(m_Fps.begin(), m_Fps.begin() + 1);
        m_Ms.erase(m_Ms.begin(), m_Ms.begin() + 1);
    }
    m_Fps.emplace_back(ImGui::GetIO().Framerate);
    m_Ms.emplace_back(App->m_Timer->GetMiliseconds());

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{

    if (!DrawMenu())
    {
        return UPDATE_STOP;
    }

    for (std::list<Panel*>::iterator it = m_Panels.begin(); it != m_Panels.end(); ++it) {
        (*it)->Draw();
    }
    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(App->m_Window->m_Window, App->m_Renderer->m_Context);

    SDL_GL_SwapWindow(App->m_Window->m_Window);

    return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
    for (std::list<Panel*>::iterator it = m_Panels.begin(); it != m_Panels.end(); ++it) {
        delete (*it);
    }
    m_Fps.clear();
    m_Ms.clear();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
    return true;
}

bool ModuleEditor::DrawMenu() 
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            if (ImGui::MenuItem("Exit")) {
                return false;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("GitHub"))
        {
            if (ImGui::MenuItem("Main Page")) {
                ShellExecuteA(NULL, "open", "https://github.com/DADSILVER/UPC-Videogame-Engine", NULL, NULL, SW_SHOWNORMAL);
            }
            if (ImGui::MenuItem("Documentation")) {
                ShellExecuteA(NULL, "open", "https://github.com/DADSILVER/UPC-Videogame-Engine/README.md", NULL, NULL, SW_SHOWNORMAL);
            }
            if (ImGui::MenuItem("Download Latest")) {
                ShellExecuteA(NULL, "open", "https://github.com/DADSILVER/UPC-Videogame-Engine/releases", NULL, NULL, SW_SHOWNORMAL);
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Windows"))
        {
            ImGui::MenuItem("About", NULL, &m_About->GetOpen());
            ImGui::MenuItem("Console Log", NULL, &m_Console->GetOpen());
            ImGui::MenuItem("Configuration", NULL, &m_ConfigWindow->GetOpen());
            ImGui::MenuItem("Model", NULL, &m_ConfigModel->GetOpen());
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    return true;
}