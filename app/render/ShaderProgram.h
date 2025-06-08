#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <string>

#include "../../glad/gl.h"
#include "../../glm/ext/matrix_float4x4.hpp"

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

    void setMatrix4(const string &name, const glm::mat4& matrix);

private:
    bool compiled = false;
    GLuint id = 0;

    bool createShader(const string &source, const GLenum shaderType, GLuint &shaderID);
};


#endif
