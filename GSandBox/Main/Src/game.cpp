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

/* OpenGL Includes */
#include "glfw_config.h"
#include <GLFW/glfw3.h>

using namespace game;
using namespace std::chrono;

/* Private variable Declarations */
GLFWwindow* window;

/* Private Function Declartations */
void error_callback(int error, const char* description);

Game::Game() {
    // Create the window for the game
    // window = glfwCreateWindow(640, 480, "Sequoia", glfwGetPrimaryMonitor(), NULL);
}

Game::~Game() {}

void Game::run() {

    if (glfwInit() != GLFW_TRUE) {
        std::cout << "GLFW could not be initialised" << std::endl;
        return;
    }

    window = glfwCreateWindow(1920, 1080, "Sequoia", NULL, NULL);
    if (window == NULL) {
        std::cout << "Window could not be created" << std::endl;
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    int frames                     = 0;
    system_clock::time_point time1 = system_clock::now();

    // Run main game loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {

        /* Render here */
        render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        // Print the FPS
        auto elapsedTime = duration_cast<milliseconds>(system_clock::now() - time1);
        if (elapsedTime.count() >= 1000) {
            std::cout << "FPS: " << frames << std::endl;
            frames = 0;
            time1  = system_clock::now();
        }

        frames++;
    }

    glfwTerminate();
}

void Game::render() {
    glClearColor(0.6f, 0.6f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}