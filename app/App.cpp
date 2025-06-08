#include "App.h"

#include <iostream>
#include <thread>

#include "../glm/vec2.hpp"
#include "../glm/gtc/matrix_transform.hpp"


using namespace std;


App::App(): window(nullptr), resourceManager(nullptr) {
}

glm::vec2 windowSize = glm::vec2(800, 600);


void sizeCallback(GLFWwindow *_, int width, int height) {
    windowSize.x = width;
    windowSize.y = height;
    glViewport(0, 0, width, height);
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

    window = glfwCreateWindow(windowSize.x, windowSize.y, "App", nullptr, nullptr);
    if (!window) {
        cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, sizeCallback);

    glfwMakeContextCurrent(window);

    if (!gladLoaderLoadGL()) {
        cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    return 0;
}

void App::run() const {
    auto spriteShaderProgram = resourceManager->loadShaders("SpriteShader", "res/shaders/vSprite.glsl",
                                                      "res/shaders/fSprite.glsl");
    if (!spriteShaderProgram) {
        cerr << "Cant create shader program: " << "SpriteShader" << endl;

        return;
    }

    auto texture = resourceManager->loadTexture("DefaultTexture", "res/textures/character.png");
    if (!texture) {
        cerr << "Cant create texture: " << "DefaultTexture" << endl;

        return;
    }

    auto sprite = resourceManager -> loadSprite("DefaultSprite","DefaultTexture","SpriteShader",150,300);
    if (!sprite) {
        cerr << "Cant create sprite: " << "DefaultSprite" << endl;

        return;
    }

    sprite -> setPosition(glm::vec2(200,100));

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(windowSize.x), 0.f,
                                           static_cast<float>(windowSize.y), -100.f, 100.f);

    spriteShaderProgram->use();
    spriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);
    spriteShaderProgram->setInt("tex", 0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        sprite -> render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}

App::~App() {
    delete resourceManager;
    glfwTerminate();
}
