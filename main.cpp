#include "app/App.h"


int main(int _, char *argv[]) {
    App *app = new App();

    if (app->initialize(argv[0]) != 0) {
        return -1;
    }

    app->run();

    delete app;

    return 0;
}
