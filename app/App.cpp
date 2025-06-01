#include "App.h"

#include <array>
#include <iostream>
#include <vector>

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

struct Scene {
    vector<Triangle *> *triangles;
    ShaderProgram *shaderProgram;
    Texture2D *texture;


    Scene(vector<Triangle *> *vector, ShaderProgram *shaderProgram, Texture2D *texture) : triangles(vector),
        shaderProgram(shaderProgram), texture(texture) {
    }
};

void triangleCallback(GLFWwindow *w, int key, int scancode, int action, int mods) {
    auto scene = static_cast<Scene *>(glfwGetWindowUserPointer(w));
    if (!scene || action != GLFW_PRESS || !scene->triangles || !
        scene->shaderProgram || !scene->texture) {
        return;
    }

    switch (key) {
        case GLFW_KEY_A:
            if (!scene->triangles->empty()) {
                scene->triangles->back()->moveLeft();
            }
            break;
        case GLFW_KEY_D:
            if (!scene->triangles->empty()) {
                scene->triangles->back()->moveRight();
            }
            break;
        case GLFW_KEY_W:
            scene->triangles->push_back(new Triangle(scene->shaderProgram, scene->texture));
            break;
        case GLFW_KEY_S: {
            if (scene->triangles->empty()) {
                break;
            }
            auto lastTr = scene->triangles->back();
            if (lastTr != nullptr) {
                scene->triangles->pop_back();
                delete lastTr;
            }
            break;
        }
        default:
            glfwSetWindowShouldClose(w, GLFW_TRUE);
    }
}

void App::run() const {
    auto shaderProgram = resourceManager->loadShaders("DefaultShader", "res/shaders/vertex.glsl",
                                                      "res/shaders/fragment.glsl");
    if (!shaderProgram) {
        cerr << "Cant create shader program: " << "DefaultShader" << endl;
    }

    auto texture = resourceManager->loadTexture("DefaultTexture", "res/textures/background.png");

    auto triangles = new vector<Triangle *>();

    triangles->push_back(new Triangle(shaderProgram, texture));

    auto scene = new Scene(triangles, shaderProgram, texture);

    glfwSetWindowUserPointer(window, scene);

    glfwSetKeyCallback(window, triangleCallback);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto tr: *triangles) {
            tr->draw();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (auto tr: *triangles) {
        delete tr;
    }

    delete triangles;

    delete scene;
}

App::~App() {
    delete resourceManager;
    glfwTerminate();
}
