#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../../glad/gl.h"


class Texture2D {
public:
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

    void bind() const;

private:
    GLuint id;
    GLenum mode;
    unsigned int width;
    unsigned int height;
};

#endif
