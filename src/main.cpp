#include <iostream>
#include <glad/glad.h>
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"
#include "Entity.h"

int main() {
    // Initialize window
    Window window(800, 600, "GamaEngine");
    if (!window.initialize()) {
        return -1;
    }

    // glfwSetKeyCallback(window.getHandle(), Window::key_callback);

    window.swapInterval(1);

    // Create shader
    Shader shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");

    // Create and initialize renderer
    Renderer renderer;
    renderer.initialize();
    renderer.setShader(&shader);

    float speed = 0.05f;
    Entity entity(0.0f, 0.0f, .2f, .2f, speed);
    entity.setColor(1.0f, 0.0f, 0.0f);  // Red
    window.setEntity(&entity);

    // Main game loop
    while (!window.shouldClose()) {

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.drawEntity(entity);

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}