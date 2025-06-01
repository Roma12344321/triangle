#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../../glad/gl.h"


class Texture2D {
public:
    Texture2D(const GLuint width, GLuint height, const unsigned char *data, const unsigned int channels = 4);
};

#endif
