#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <map>
#include <string>

#include "../../glad/gl.h"
#include "../../glm/vec2.hpp"


class Texture2D {
public:
    struct SubTexture2D {
        glm::vec2 leftBottomUV;
        glm::vec2 rightTopUV;

        SubTexture2D(const glm::vec2 &leftBottomUV, const glm::vec2 &rightTopUV): leftBottomUV(leftBottomUV),
            rightTopUV(rightTopUV) {
        }

        SubTexture2D() : leftBottomUV(0.f), rightTopUV(1.f) {
        }
    };

    Texture2D(
        const GLuint width,
        GLuint height,
        const unsigned char *data,
        const unsigned int channels = 4,
        const GLenum filter = GL_LINEAR,
        const GLenum wrapMode = GL_CLAMP_TO_EDGE
    );

    Texture2D() = delete;

    Texture2D(const Texture2D &) = delete;

    Texture2D &operator=(const Texture2D &) = delete;

    Texture2D &operator =(Texture2D &&texture2d) noexcept;

    Texture2D(Texture2D &&texture2d) noexcept;

    ~Texture2D();

    void addSubTexture(const std::string &name, const glm::vec2 &leftBottomUV, const glm::vec2 &rightTopUV);

    const SubTexture2D &getSubTexture(const std::string &name) const;

    void bind() const;

    unsigned int getWidth() const {
        return width;
    };

    unsigned int getHeight() const {
        return height;
    }

private:
    GLuint id;
    GLenum mode;
    unsigned int width;
    unsigned int height;

    std::map<std::string, SubTexture2D> subTextures;
};

#endif
