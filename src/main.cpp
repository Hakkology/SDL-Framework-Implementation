#include <iostream>

#include "app.h"

int main() {

    if (App::Singleton().Init(SCREEN_WIDTH, SCREEN_HEIGHT, MAGNIFICATION))
    {
        App::Singleton().Run();
    }
    
    return 0;
}