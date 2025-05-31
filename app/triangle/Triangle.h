//
// Created by romam on 31.05.2025.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>

#include "../../glad/gl.h"
#include "../../GLFW/glfw3.h"

using namespace std;

class Triangle {
    array<GLfloat, 9> points;

    const array<GLfloat, 9> colors = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    GLuint shaderProgram;
    GLuint vao;

    public:
    Triangle(const array<GLfloat, 9> &pts);
    void draw() const;

};



#endif //TRIANGLE_H
