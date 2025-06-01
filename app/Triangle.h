#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>

#include "../glad/gl.h"
#include "render/ShaderProgram.h"
#include "render/Texture2D.h"

using namespace std;

class Triangle {
    array<GLfloat, 9> points = {
        0.0f, 0.5f, 0,
        0.5f, -0.5f, 0,
        -0.5f, -0.5f, 0
    };

    const array<GLfloat, 9> colors = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    array<GLfloat, 6> textureCoordinates = {
        0.5f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };

    ShaderProgram *shaderProgram;
    Texture2D* texture;

    GLuint vao;
    GLuint pointsVbo;
    GLuint colorsVbo;
    GLuint texturesVbo;

    void changeState() const;

public:
    explicit Triangle(ShaderProgram *program, Texture2D *texture);

    Triangle() = default;

    ~Triangle();

    void draw() const;

    void moveLeft();

    void moveRight();
};


#endif
