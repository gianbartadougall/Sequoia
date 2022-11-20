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

/* GLEW Includes. This must be included before GLFW includes */
#define GLEW_STATIC
#include <GL/glew.h>

/* GLFW Includes */
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

    /****** START CODE BLOCK ******/
    // Description: Testing rendering

    // Create vertices of traingle to render
    float vertices[] = {
        0.0f,  0.5f,  // Vertex 1 (X, Y)
        0.5f,  -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f  // Vertex 3 (X, Y)
    };

    // Create vertex buffer object. This
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer

    // Make the buffer that was just created active
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Adding data to buffer doesn't depend on the id of the buffer but which buffer
    // is currently active
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
    )glsl";

    const char* fragmentSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main()
    {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
    )glsl";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);

    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindFragDataLocation(shaderProgram, 0, "outColor");

    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");

    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(posAttrib);

    GLuint vao;
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    /****** END CODE BLOCK ******/

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
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glClearColor(0.6f, 0.6f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}