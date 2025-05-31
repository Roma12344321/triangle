#include "App.h"

#include <array>
#include <iostream>

#include "Triangle.h"

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


App::App() {
}


int App::initialize(const char *executablePath) {
    resourceManager = new ResourceManager(executablePath);

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
    auto shaderProgram = resourceManager->loadShaders("DefaultShader", "res/shaders/vertex.glsl",
                                                      "res/shaders/fragment.glsl");
    if (!shaderProgram) {
        cerr << "Cant create shader program: " << "DefaultShader" << endl;
    }

    const auto triangle = new Triangle(points, shaderProgram);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        triangle->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete triangle;
}

App::~App() {
    glfwTerminate();
    delete resourceManager;
}
