#include "Texture2D.h"


Texture2D::Texture2D(
    const GLuint width,
    GLuint height,
    const unsigned char *data,
    const unsigned int channels,
    const GLenum filter,
    const GLenum wrapMode)
    : width(width), height(height) {
    switch (channels) {
        case 4:
            mode = GL_RGBA;

            break;
        case 3:
            mode = GL_RGB;

            break;
        default:
            mode = GL_RGBA;

            break;
    }

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture2D &Texture2D::operator=(Texture2D &&texture2d) noexcept {
    glDeleteTextures(1, &id);
    id = texture2d.id;
    texture2d.id = 0;
    mode = texture2d.mode;
    width = texture2d.width;
    height = texture2d.height;

    return *this;
}

Texture2D::Texture2D(Texture2D &&texture2d) noexcept {
    id = texture2d.id;
    texture2d.id = 0;
    mode = texture2d.mode;
    width = texture2d.width;
    height = texture2d.height;
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &id);
}

void Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, id);
}
