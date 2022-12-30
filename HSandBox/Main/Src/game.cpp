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

/* Private Function Declartations */

Game::Game() {

}

Game::~Game() {

}

uint8_t Game::run() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return 1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    printf("%u\n", vertexBuffer);
    return 0;
    // Creating a new matrix testing
    // Matrix4f m1, m2;
    // m1.scale(2);
    // m2.scale(3);
    // m1.multiply(&m2);
    // m1.print()
    const char* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
    )glsl";


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
