#include <iostream>
#include "Game.h"

int main()
{
    // Init srand
    srand(static_cast<unsigned>(time(NULL)));

    // Init Game engine
    Game game; 

    // Game loop
    while (game.getWindowIsOpen()) // check if true
    {      

        // Update
        game.update();

        // Render
        game.render();


    }

    // End of application
    return 0;
}