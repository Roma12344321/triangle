#ifndef APP_H
#define APP_H
#include "../glad/gl.h"
#include "../GLFW/glfw3.h"


class App {
public:
    App();
    int initialize();

    static void terminate();
    void run() const;

private:
    GLFWwindow* window;
};

#endif