#ifndef APP_H
#define APP_H
#include "../glad/gl.h"
#include "../GLFW/glfw3.h"
#include "resources/ResourceManager.h"


class App {
public:
    App();
    int initialize(const char* executablePath);

    void run() const;

    ~App();

private:
    GLFWwindow* window;
    ResourceManager* resourceManager;
};

#endif