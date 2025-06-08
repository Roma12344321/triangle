#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>

#include "../glad/gl.h"
#include "../glm/vec2.hpp"
#include "render/ShaderProgram.h"
#include "render/Texture2D.h"

using namespace std;

class Triangle {
    array<GLfloat, 9> points;

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
    glm::vec2 *windowSize;
    glm::mat4 modelMatrix;
    glm::vec3 position;

public:
    explicit Triangle(ShaderProgram *program, Texture2D *texture,glm::vec2 *windowSize);

    void moveLeft(const float value);

    Triangle() = default;

    ~Triangle();

    void draw() const;
};


#endif
