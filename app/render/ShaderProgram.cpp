#include "ShaderProgram.h"

#include <filesystem>
#include <iostream>

constexpr int BUFF_SIZE = 1024;

ShaderProgram::ShaderProgram(const string &vertexShader, const string &fragmentShader) {
    GLuint vertexShaderID = 0;
    if (!this->createShader(vertexShader, GL_VERTEX_SHADER,vertexShaderID)) {
        cerr << "Error compling vertex shader" << endl;

        return;
    }

    GLuint fragmentShaderID = 0;
    if (!this->createShader(fragmentShader, GL_FRAGMENT_SHADER,fragmentShaderID)) {
        cerr << "Error compling fragment shader" << endl;
        glDeleteShader(vertexShaderID);

        return;
    }

    id = glCreateProgram();

    glAttachShader(id, vertexShaderID);
    glAttachShader(id, fragmentShaderID);

    glLinkProgram(id);

    GLint status = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &status);

    if (!status) {
        GLchar infoLog[BUFF_SIZE] = {};
        glGetShaderInfoLog(id, BUFF_SIZE, nullptr, infoLog);
        cerr << "Shader link error: " << infoLog << endl;

        compiled = false;
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        return;
    }

    compiled = true;
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id);
}

bool ShaderProgram::createShader(const string &source, const GLenum shaderType, GLuint &shaderID) {
    shaderID = glCreateShader(shaderType);
    const char* code = source.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);

    glCompileShader(shaderID);

    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[BUFF_SIZE] = {};
        glGetShaderInfoLog(shaderID, BUFF_SIZE, nullptr, infoLog);
        cerr << "Shader compilation error: " << infoLog << endl;

        return false;
    }

    return true;
}

ShaderProgram & ShaderProgram::operator=(ShaderProgram &&shaderProgram) noexcept {
    glDeleteProgram(id);

    id = shaderProgram.id;

    compiled = shaderProgram.compiled;

    shaderProgram.id = 0;
    shaderProgram.compiled = false;

    return *this;
}

ShaderProgram::ShaderProgram(ShaderProgram &&shaderProgram) noexcept {
    id = shaderProgram.id;

    compiled = shaderProgram.compiled;

    shaderProgram.id = 0;
    shaderProgram.compiled = false;
}

void ShaderProgram::use() const {
    glUseProgram(id);
}
