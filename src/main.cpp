#include <iostream>
#include <glad/glad.h>
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"

int main() {
    // Initialize window
    Window window(800, 600, "GamaEngine");
    if (!window.initialize()) {
        return -1;
    }

    // Create shader
    Shader shader("./shaders/vertex.glsl", "./shaders/fragment.glsl");

    // Create and initialize renderer
    Renderer renderer;
    renderer.initialize();
    renderer.setShader(&shader);

    // Main game loop
    while (!window.shouldClose()) {
        window.pollEvents();

        // Clear screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render
        renderer.draw();

        window.swapBuffers();
    }

    return 0;
}