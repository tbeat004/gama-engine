#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(800, 600, "GamaEngine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}