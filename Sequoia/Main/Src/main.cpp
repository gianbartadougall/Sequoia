#include <iostream>

/* Private Includes */
#include "game.h"
#include <glfw3.h>

using namespace game;

int main(void) {

    std::cout << "This is a test!!!" << std::endl;

    Game game;
    game.run();
    
    return 0;

}