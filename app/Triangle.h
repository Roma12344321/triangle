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
    GLuint pointsVbo;
    GLuint colorsVbo;

    void changeState() const;

public:
    explicit Triangle(const array<GLfloat, 9> &pts,ShaderProgram* program);

    Triangle() = default;

    ~Triangle();

    void draw() const;

    void moveLeft();

    void moveRight();
};


#endif
