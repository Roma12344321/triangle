#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>

#include "../glad/gl.h"
#include "../GLFW/glfw3.h"
#include "render/ShaderProgram.h"

using namespace std;

class Triangle {
    array<GLfloat, 9> points;

    const array<GLfloat, 9> colors = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    ShaderProgram* shaderProgram;

    GLuint vao;
    bool compiled = true;

public:
    explicit Triangle(const array<GLfloat, 9> &pts);

    void draw() const;

    ~Triangle();

    bool isCompiled() const {
        return compiled;
    }
};


#endif
