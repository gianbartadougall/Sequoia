#include <iostream>

/* Private Includes */
#include "game.h"

using namespace game;

//int hello(void);

int main(void) {

    std::cout << "The main function ran" << std::endl;

    Game game;
    std::cout << "initalisised instance of class" << std::endl;
    game.run();
    
    return 0;

}