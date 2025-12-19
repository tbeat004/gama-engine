#pragma once

#include "Shader.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void initialize();
    void draw();
    void setShader(Shader* shader);

private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    Shader* m_shader;

    void setupBuffers();
    void setupVertexAttributes();
};
