#pragma once

#include "Window.h"
#include <Renderer.h>
#include <LuaEngine.h>

namespace GamaEngine {

class EditorApp {
public:
    EditorApp();
    ~EditorApp();
    
    void Run();
    
private:
    void Init();
    void Shutdown();
    void Update();
    void Render();
    void RenderUI();
    
    Window* m_Window;
    Renderer* m_Renderer;
    bool m_Running;
};

} // namespace GamaEngine
