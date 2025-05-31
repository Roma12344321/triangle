#include "Triangle.h"


namespace triangle {
    const char *vertexShader = R"glsl(
    #version 330 core
    layout(location = 0) in vec3 vertex_position;
    layout(location = 1) in vec3 vertex_color;
    out vec3 color;
    void main() {
        color = vertex_color;
        gl_Position = vec4(vertex_position, 1.0);
    }
)glsl";

    const char *fragmentShader = R"glsl(
    #version 330
    in vec3 color;
    out vec4 frag_color;
    void main() {
       frag_color = vec4(color, 1.0);
    }
)glsl";
}


Triangle::Triangle(const array<GLfloat, 9> &pts) {
    points = pts;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &triangle::vertexShader, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &triangle::fragmentShader, nullptr);
    glCompileShader(fs);

    auto shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);

    glLinkProgram(shaderProgram);

    this->shaderProgram = shaderProgram;

    glDeleteShader(vs);
    glDeleteShader(fs);

    GLuint pointsVbo = 0;
    glGenBuffers(1, &pointsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);

    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(GLfloat), points.data(), GL_STATIC_DRAW);

    GLuint colorsVbo = 0;
    glGenBuffers(1, &colorsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);

    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    this->vao = vao;

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, nullptr);
}

void Triangle::draw() const {
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
