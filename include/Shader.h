#pragma once

#include <string>
#include <glad/glad.h>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    GLuint getProgram() const { return m_program; }
    GLint getAttribLocation(const std::string& name) const;
    GLint getUniformLocation(const std::string& name) const;

private:
    GLuint m_program;
    GLuint m_vertexShader;
    GLuint m_fragmentShader;

    std::string loadShaderFromFile(const std::string& filepath);
    bool compileShader(GLuint shader, const std::string& source, const std::string& type);
    bool linkProgram();
};
