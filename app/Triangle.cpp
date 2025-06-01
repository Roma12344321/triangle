#include "Triangle.h"

#include <iostream>
#include <string>

using namespace std;

Triangle::Triangle(const array<GLfloat, 9> &pts, ShaderProgram *program) : points(pts), shaderProgram(program) {
    glGenBuffers(1, &pointsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);

    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), points.data(), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);

    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, nullptr);
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

    glDeleteVertexArrays(1, &vao);
}

void Triangle::draw() const {
    shaderProgram->use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
