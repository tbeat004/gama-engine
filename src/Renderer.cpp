#include "Renderer.h"

Renderer::Renderer()
    : m_vao(0), m_vbo(0), m_ebo(0), m_shader(nullptr) {
}

Renderer::~Renderer() {
    if (m_vao) glDeleteVertexArrays(1, &m_vao);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
}

void Renderer::initialize() {
    setupBuffers();
}

void Renderer::setShader(Shader* shader) {
    m_shader = shader;
    if (m_shader) {
        m_shader->use();
        setupVertexAttributes();
    }
}

void Renderer::setupBuffers() {
    float vertices[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
    };

    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Generate and bind VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Generate and setup VBO
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Generate and setup EBO
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}

void Renderer::setupVertexAttributes() {
    if (!m_shader) return;

    glBindVertexArray(m_vao);

    // Position attribute
    GLint posAttrib = m_shader->getAttribLocation("position");
    if (posAttrib != -1) {
        glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
        glEnableVertexAttribArray(posAttrib);
    }

    // Color attribute
    GLint colorAttrib = m_shader->getAttribLocation("color");
    if (colorAttrib != -1) {
        glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(colorAttrib);
    }

    // Set uniform if it exists
    GLint uniColor = m_shader->getUniformLocation("triangleColor");
    if (uniColor != -1) {
        glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
    }
}

void Renderer::draw() {
    if (!m_shader) return;

    m_shader->use();
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
