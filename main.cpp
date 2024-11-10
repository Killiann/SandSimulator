#include <SFML/Graphics.hpp>
#include "application.h"

int main()
{    
    application app; 

    while (app.is_running())
    {
        app.run();
    }

    app.end();
    return 0;
}