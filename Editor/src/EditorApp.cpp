#include "EditorApp.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

namespace GamaEngine {

EditorApp::EditorApp() 
    : m_Window(nullptr), m_Renderer(nullptr), m_Running(false) {
}

EditorApp::~EditorApp() {
    Shutdown();
}

void EditorApp::Init() {
    std::cout << "=== Gama Engine Editor Starting ===" << std::endl;
    
    // Create window
    m_Window = new Window(1920, 1080, "Gama Engine Editor");
    m_Window->initialize();
    m_Renderer = new Renderer();
    
    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    
    ImGui::StyleColorsDark();
    
    // Initialize ImGui for GLFW + OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(m_Window->getHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 410");
    
    m_Running = true;
    
    std::cout << "Editor initialized successfully" << std::endl;
}

void EditorApp::Shutdown() {
    if (m_Window) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        
        delete m_Renderer;
        delete m_Window;
        
        std::cout << "Editor shutdown complete" << std::endl;
    }
}

void EditorApp::Run() {
    Init();
    
    while (m_Running && !m_Window->shouldClose()) {
        m_Window->pollEvents();
        
        Update();
        Render();
    }
}

void EditorApp::Update() {
    // Update logic here
}

void EditorApp::Render() {
    m_Renderer->clear();
    
    // Start ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    RenderUI();
    
    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    // Update and render additional platform windows
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
    
    m_Window->swapBuffers();
}

void EditorApp::RenderUI() {
    // Main menu bar
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Scene")) { }
            if (ImGui::MenuItem("Open Scene")) { }
            if (ImGui::MenuItem("Save Scene")) { }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) {
                m_Running = false;
            }
            ImGui::EndMenu();
        }
        
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "Ctrl+Z")) { }
            if (ImGui::MenuItem("Redo", "Ctrl+Y")) { }
            ImGui::EndMenu();
        }
        
        ImGui::EndMainMenuBar();
    }
    
    // Dockspace
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleVar(3);
    
    ImGuiID dockspace_id = ImGui::GetID("EditorDockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
    
    ImGui::End();
    
    // Scene Hierarchy panel
    ImGui::Begin("Scene Hierarchy");
    ImGui::Text("Scene objects will appear here");
    ImGui::End();
    
    // Inspector panel
    ImGui::Begin("Inspector");
    ImGui::Text("Object properties will appear here");
    ImGui::End();
    
    // Viewport panel
    ImGui::Begin("Viewport");
    ImGui::Text("3D scene rendering will appear here");
    ImVec2 viewportSize = ImGui::GetContentRegionAvail();
    ImGui::Text("Viewport Size: %.0f x %.0f", viewportSize.x, viewportSize.y);
    ImGui::End();
}

} 
