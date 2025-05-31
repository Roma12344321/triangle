#include "App.h"

#include <array>
#include <iostream>

using namespace std;


void escapeCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        cout << "ESCAPE" << endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void keyCallbacks(GLFWwindow *window, int key, int scancode, int action, int mods) {
    escapeCallback(window, key, scancode, action, mods);
}

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


App::App() {}


int App::initialize() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1920, 1080, "Rotating Triangle", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoaderLoadGL()) {
        cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glfwSetKeyCallback(window, keyCallbacks);

    return 0;
}

const array<GLfloat, 9> points = {
    0.0f, 0.5f, 0,
    0.5f, -0.5f, 0,
    -0.5f, -0.5f, 0
};

void App::run() const {
    const auto triangle = new Triangle(points);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        triangle->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete triangle;
}

void App::terminate() {
    glfwTerminate();
}
