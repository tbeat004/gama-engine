#pragma once

#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool initialize();
    bool shouldClose() const;
    void pollEvents();
    void swapBuffers();
    GLFWwindow* getHandle() { return m_window; }

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;
};
