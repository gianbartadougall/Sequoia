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
#define GLEW_STATIC
//#define GLFW_DLL
#include "GL/glew.h"
#include "GLFW/glfw3.h"
// #include "matrix4f.h"

using namespace game;
// using namespace matrix4f;
using namespace std::chrono;

GLFWwindow* window;

/* Private Function Declartations */

Game::Game() {
    char window_title[100] = "EPIC_PHYSICS_SIMULATION\0";

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "failed to initalise glfw" << std::endl;
        exit(1);
    }
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, window_title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cout << "window failed to launch" << std::endl;
        exit(1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

}

Game::~Game() {

}

uint8_t Game::run() {

    int frames = 0;
    system_clock::time_point time1 = system_clock::now();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        // Print the FPS
        auto elapsedTime = duration_cast<milliseconds>(system_clock::now() - time1);
        if (elapsedTime.count() >= 1000) {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            time1 = system_clock::now();
        }

        frames++;
    }


    // Create a game loop
    while (1) {
    }

}
