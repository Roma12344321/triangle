#include "Triangle.h"

#include <iostream>

using namespace std;

Triangle::Triangle(ShaderProgram *program, Texture2D *texture) : shaderProgram(program), texture(texture) {
    glGenBuffers(1, &pointsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);

    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), points.data(), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);

    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &texturesVbo);
    glBindBuffer(GL_ARRAY_BUFFER, texturesVbo);

    glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(GLfloat), textureCoordinates.data(),
                 GL_DYNAMIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, nullptr);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, texturesVbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 0, nullptr);
    program->use();
    program->setInt("tex", 0);

    glBindVertexArray(0);
}

void Triangle::changeState() const {
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), points.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void Triangle::moveLeft() {
    points[0] -= 0.1f;
    points[3] -= 0.1f;
    points[6] -= 0.1f;

    changeState();
}

void Triangle::moveRight() {
    points[0] += 0.1f;
    points[3] += 0.1f;
    points[6] += 0.1f;

    changeState();
}

Triangle::~Triangle() {
    glDeleteBuffers(1, &pointsVbo);
    glDeleteBuffers(1, &colorsVbo);
    glDeleteBuffers(1, &texturesVbo);
    glDeleteVertexArrays(1, &vao);
}

void Triangle::draw() const {
    shaderProgram->use();
    glBindVertexArray(vao);
    texture->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
