/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for game
 * @version 0.1
 * @date --
 * 
 * @copyright Copyright (c) 
 * 
 */
/* Public Includes */
#include <iostream>
#include <chrono> // Required for getting system time
// #include <ctime>    

/* Private Includes */
#include "game.h"
// #include "matrix4f.h"

using namespace game;
// using namespace matrix4f;
using namespace std::chrono;

/* Private Function Declartations */

Game::Game() {

}

Game::~Game() {

}

void Game::run() {

    // Creating a new matrix testing
    // Matrix4f m1, m2;
    // m1.scale(2);
    // m2.scale(3);
    // m1.multiply(&m2);
    // m1.print();

    int frames = 0;
    system_clock::time_point time1 = system_clock::now();
    // Create a game loop
    while (1) {

        // Print the FPS
        auto elapsedTime = duration_cast<milliseconds>(system_clock::now() - time1);
        if (elapsedTime.count() >= 1000) {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            time1 = system_clock::now();
        }

        frames++;
    }

}
