#include "Sprite.h"

#include "../../glm/ext/matrix_transform.hpp"


Sprite::Sprite(
    const Texture2D *texture,
    const std::string &initialSubTexture,
    ShaderProgram *shaderProgram,
    const glm::vec2 &position,
    const glm::vec2 &size,
    const float rotation) : texture(texture), shaderProgram(shaderProgram),
                            position(position), size(size), rotation(rotation) {
    const GLfloat vertexCoords[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,

        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
    };

    auto subTexture = this->texture->getSubTexture(initialSubTexture);

    const GLfloat textCoords[] = {
        subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
        subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
        subTexture.rightTopUV.x, subTexture.rightTopUV.y,

        subTexture.rightTopUV.x, subTexture.rightTopUV.y,
        subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
        subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    glGenBuffers(1, &vertexVbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glGenBuffers(1, &textureVbo);
    glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textCoords), &textCoords, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Sprite::~Sprite() {
    glDeleteBuffers(1, &vertexVbo);
    glDeleteBuffers(1, &textureVbo);
    glDeleteVertexArrays(1, &vao);
}

void Sprite::render() const {
    shaderProgram->use();

    glm::mat4 model(1.0f);

    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    glBindVertexArray(vao);

    shaderProgram->setMatrix4("modelMat", model);

    glActiveTexture(GL_TEXTURE0);
    texture->bind();

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Sprite::setPosition(const glm::vec2 &position) {
    this->position = position;
}

void Sprite::setSize(const glm::vec2 &size) {
    this->size = size;
}

void Sprite::setRotation(const float rotation) {
    this->rotation = rotation;
}
