#include "app/App.h"

#define begin {;
#define end };


int main()
begin
    App *app = new App();

    if (app->initialize() != 0)
    begin
        return -1;
    end

    app->run();

    App::terminate();

    delete app;

    return 0;
end
