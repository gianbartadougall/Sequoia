#include <iostream>

/* Private Includes */
#include "game.h"

/* OpenGL Includes */
#include "glfw_config.h"
#include <GLFW/glfw3.h>

using namespace game;

int main(void) {

    Game game;
    game.run();

    return 0;
}