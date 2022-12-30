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
#define GLEW_STATIC
#include "GL/glew.h"

#include "GLFW/glfw3.h"

// #include "matrix4f.h"
#include "game.h"

using namespace game;
// using namespace matrix4f;
using namespace std::chrono;

GLFWwindow* window;

/* Private Function Declartations */

Game::Game() {

    /* Initialize the library */
    if (!glfwInit()) {
        std::cout << "failed to initalise glfw" << std::endl;
        exit(1);
    }
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Sequoia", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cout << "window failed to launch" << std::endl;
        exit(1);
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW didnt init properly" << std::endl;
        exit(1);
    }

}

Game::~Game() {

}

void Game::run() {

    int frames = 0;
	system_clock::time_point time1 = system_clock::now();


	// Run main game loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {

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
