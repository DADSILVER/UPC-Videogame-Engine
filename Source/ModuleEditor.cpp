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

    ImGui::StyleColorsLight();

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
        m_Fps.erase(m_Fps.begin(), m_Fps.begin()+50);
    }
    m_Fps.emplace_back(ImGui::GetIO().Framerate);

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
    //NewTestImgUI();
    NewHelloWorld();
    

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
    //glClearColor(m_clear_color.x * m_clear_color.w, m_clear_color.y * m_clear_color.w, m_clear_color.z * m_clear_color.w, m_clear_color.w);
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
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    return false;
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
                ShellExecuteA(NULL, "open", "https://github.com/DADSILVER/UPC-Videogame-Engine", NULL, NULL, SW_SHOWNORMAL);
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


void ModuleEditor::NewTestImgUI() 
{
    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
    //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    //ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&m_clear_color); // Edit 3 floats representing a color

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

void ModuleEditor::NewHelloWorld()
{
    static char buf[32];
    //static float f=10.0f;
    ImGui::Begin("Hello, world 2!");
    ImGui::Text("Hello, world %d", 123);
    ImGui::Checkbox("Demo Window", &show_demo_window);

    if (show_demo_window)
    {
        ImGui::ShowDemoWindow(&show_demo_window);
    }
    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    ImGui::End();

}

