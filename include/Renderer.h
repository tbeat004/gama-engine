#pragma once

#include <glad/glad.h>
#include "Shader.h"
#include "Entity.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void initialize();
    void drawEntity(const Entity& entity);
    void setShader(Shader* shader);

private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    Shader* m_shader;

    void setupBuffers();
    void setupVertexAttributes();
    void updateVertexData(const Entity& entity);
};
