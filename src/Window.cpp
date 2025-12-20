#include "Window.h"
#include <iostream>

Window::Window(int width, int height, const std::string& title)
    : m_window(nullptr), m_width(width), m_height(height), m_title(title) {
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

bool Window::initialize() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // Set OpenGL version hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // Set viewport
    glViewport(0, 0, m_width, m_height);

    // Set user pointer and callbacks
    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, key_callback);

    return true;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    glfwSwapBuffers(m_window);
}

void Window::swapInterval(int interval) {
    glfwSwapInterval(interval);
}

void Window::key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
    Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);

    if (window->m_entity) {
        if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
            window->m_entity->move(window->m_entity->getSpeed(), 0.0f);
        }

        if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
            window->m_entity->move(-window->m_entity->getSpeed(), 0.0f);
        }
    }
}