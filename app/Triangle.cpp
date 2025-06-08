#include "Triangle.h"

#include <iostream>

#include "../glm/gtc/matrix_transform.hpp"


using namespace std;

Triangle::Triangle(ShaderProgram *program, Texture2D *texture, glm::vec2 *windowSize) : shaderProgram(program),
    texture(texture), windowSize(windowSize) {
    points = {
        0.0f, windowSize->y/4, 0.0f,
        windowSize->x/4, -windowSize->y/4, 0.0f,
        -windowSize->x/4, -windowSize->y/4, 0.0f
    };
    glGenBuffers(1, &pointsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);

    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), points.data(), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);

    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &texturesVbo);
    glBindBuffer(GL_ARRAY_BUFFER, texturesVbo);

    glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(GLfloat), textureCoordinates.data(),
                 GL_STATIC_DRAW);

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

    shaderProgram->use();
    shaderProgram->setInt("tex", 0);

    modelMatrix = glm::mat4(1.f);
    position = glm::vec3(windowSize->x/2, windowSize->y/2, 0.f);
    modelMatrix = glm::translate(modelMatrix, position);
    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(windowSize->x), 0.f,
                                            static_cast<float>(windowSize->y), -100.f, 100.f);

    shaderProgram->setMatrix4("projectionMat", projectionMatrix);

    glBindVertexArray(0);
}

void Triangle::moveLeft(const float value) {
    modelMatrix = glm::mat4(1.f);
    position = glm::vec3(position.x - value, position.y, 0.f);
    modelMatrix = glm::translate(modelMatrix, position);
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
    shaderProgram->setMatrix4("modelMat", modelMatrix);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}
