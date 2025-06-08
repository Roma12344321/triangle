#include "App.h"

#include <iostream>
#include <thread>

#include "../glm/vec2.hpp"
#include "../glm/gtc/matrix_transform.hpp"


using namespace std;


App::App(): window(nullptr), resourceManager(nullptr) {
}

glm::vec2 windowSize = glm::vec2(1920, 1080);


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

    vector<string> subTextureNames = {
        "topLeft",
        "topCenter",
        "topRight",
        "centerLeft",
        "centerCenter",
        "centerRight",
        "bottomLeft",
        "bottomCenter",
        "bottomRight"
    };

    auto textureAtlas = resourceManager->loadTextureAtlas("DefaultTextureAtlas", "res/textures/character.png",
                                                          subTextureNames, 384 / 3, 384 / 3);

    if (!textureAtlas) {
        cerr << "Cant create texture atlas: " << "DefaultTextureAtlas" << endl;

        return;
    }


    auto animatedSprite = resourceManager->loadAnimatedSprite("DefaultAnimatedSprite", "DefaultTextureAtlas",
                                                              "SpriteShader", windowSize.x / 8, windowSize.y / 4,
                                                              "topLeft");
    if (!animatedSprite) {
        cerr << "Cant create animated sprite: " << "DefaultAnimatedSprite" << endl;
        return;
    }
    vector<pair<string, uint64_t> > characterState;

    for (auto sub_texture_name: subTextureNames) {
        characterState.emplace_back(make_pair<string, uint64_t>(std::move(sub_texture_name), 165000000));
    }

    animatedSprite->insertState("characterState", characterState);
    animatedSprite->setState("characterState");


    glm::vec2 screenCenter = windowSize * 0.5f;
    glm::vec2 halfSprite = glm::vec2(windowSize.x / 8, windowSize.y / 4) * 0.5f;

    glm::vec2 pos = screenCenter - halfSprite;
    animatedSprite->setPosition(pos);

    glm::mat4 projectionMatrix = glm::ortho(0.f, windowSize.x, 0.f,
                                            windowSize.y, -100.f, 100.f);

    spriteShaderProgram->use();
    spriteShaderProgram->setInt("tex", 0);
    spriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

    auto lastTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window)) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
        lastTime = currentTime;
        animatedSprite->update(duration);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        animatedSprite->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

App::~App() {
    delete resourceManager;
    glfwTerminate();
}
