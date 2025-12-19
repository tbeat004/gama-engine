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
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    // Generate and bind VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Generate VBO (empty for now, will be filled per entity)
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, nullptr, GL_DYNAMIC_DRAW);  // 4 vertices * 5 floats each

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
}

void Renderer::updateVertexData(const Entity& entity) {
    // Calculate entity corners based on position and size
    float halfWidth = entity.getWidth() / 2.0f;
    float halfHeight = entity.getHeight() / 2.0f;
    float x = entity.getX();
    float y = entity.getY();
    float r = entity.getR();
    float g = entity.getG();
    float b = entity.getB();

    // Generate vertices for a quad centered at entity position
    float vertices[] = {
        // Position (x, y)       // Color (r, g, b)
        x - halfWidth, y + halfHeight, r, g, b,  // Top-left
        x + halfWidth, y + halfHeight, r, g, b,  // Top-right
        x + halfWidth, y - halfHeight, r, g, b,  // Bottom-right
        x - halfWidth, y - halfHeight, r, g, b   // Bottom-left
    };

    // Update VBO with new vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
}

void Renderer::drawEntity(const Entity& entity) {
    if (!m_shader) return;

    // Generate vertices from entity data
    updateVertexData(entity);

    // Draw
    m_shader->use();
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
