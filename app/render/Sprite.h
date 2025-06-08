#ifndef SPRITE_H
#define SPRITE_H
#include "ShaderProgram.h"
#include "Texture2D.h"


class Sprite {
public:
    Sprite(
        const Texture2D *texture,
        const std::string &initialSubTexture,
        ShaderProgram *shaderProgram,
        const glm::vec2 &position = glm::vec2(0.0f),
        const glm::vec2 &size = glm::vec2(1.0f),
        const float rotation = 0.0f);

    virtual ~Sprite();

    Sprite(const Sprite &) = delete;

    Sprite &operator=(const Sprite &) = delete;

    virtual void render() const;

    void setPosition(const glm::vec2 &position);

    void setSize(const glm::vec2 &size);

    void setRotation(const float rotation);

protected:
    const Texture2D *texture;
    ShaderProgram *shaderProgram;
    glm::vec2 position;
    glm::vec2 size;
    float rotation;

    GLuint vao;
    GLuint vertexVbo;
    GLuint textureVbo;
};


#endif //SPRITE_H
