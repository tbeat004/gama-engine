#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    : m_program(0), m_vertexShader(0), m_fragmentShader(0) {
    
    // Load shader sources
    std::string vertexSource = loadShaderFromFile(vertexPath);
    std::string fragmentSource = loadShaderFromFile(fragmentPath);

    if (vertexSource.empty() || fragmentSource.empty()) {
        std::cerr << "Failed to load shader files" << std::endl;
        return;
    }

    // Create and compile shaders
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (!compileShader(m_vertexShader, vertexSource, "VERTEX")) {
        return;
    }

    if (!compileShader(m_fragmentShader, fragmentSource, "FRAGMENT")) {
        return;
    }

    // Link shader program
    if (!linkProgram()) {
        return;
    }

    // Clean up individual shaders (they're linked into the program now)
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
}

Shader::~Shader() {
    if (m_program) {
        glDeleteProgram(m_program);
    }
}

void Shader::use() const {
    glUseProgram(m_program);
}

GLint Shader::getAttribLocation(const std::string& name) const {
    return glGetAttribLocation(m_program, name.c_str());
}

GLint Shader::getUniformLocation(const std::string& name) const {
    return glGetUniformLocation(m_program, name.c_str());
}

std::string Shader::loadShaderFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    
    return buffer.str();
}

bool Shader::compileShader(GLuint shader, const std::string& source, const std::string& type) {
    const char* sourcePtr = source.c_str();
    glShaderSource(shader, 1, &sourcePtr, nullptr);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

bool Shader::linkProgram() {
    m_program = glCreateProgram();
    glAttachShader(m_program, m_vertexShader);
    glAttachShader(m_program, m_fragmentShader);
    glLinkProgram(m_program);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}
