#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <string>

#include "../../glad/gl.h"

using namespace std;


class ShaderProgram {
public:
    ShaderProgram(const string &vertexShader, const string &fragmentShader);

    ~ShaderProgram();

    ShaderProgram() = delete;

    ShaderProgram(const ShaderProgram &) = delete;

    ShaderProgram &operator=(const ShaderProgram &) = delete;

    ShaderProgram &operator=(ShaderProgram &&shaderProgram) noexcept;

    ShaderProgram(ShaderProgram &&shaderProgram) noexcept;

    bool isCompiled() const { return compiled; };

    void use() const;

    void setInt(const string &name, const GLint value);

private:
    bool compiled = false;
    GLuint id = 0;

    bool createShader(const string &source, const GLenum shaderType, GLuint &shaderID);
};



#endif
