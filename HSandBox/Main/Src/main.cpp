#include <iostream>

/* Private Includes */
#include "game.h"

using namespace game;

//int hello(void);

int main(void) {

    std::cout << "The number is " << std::endl;

    Game game;
    game.run();
    
    return 0;

}