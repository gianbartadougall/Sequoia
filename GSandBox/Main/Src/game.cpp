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
#include <string>
#include <cmath>

/* Private Includes */
#include "game.h"
#include "fileHandler.h"

/* GLEW Includes. This must be included before GLFW includes */
#define GLEW_STATIC
#include <GL/glew.h>

/* GLFW Includes */
// #include "glfw_config.h"
#include <GLFW/glfw3.h>

using namespace game;
using namespace std::chrono;

/* Private variable Declarations */
GLFWwindow* window;

// // Shader sources
const GLchar* vertexSource   = R"glsl(
    #version 150 core
    in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
)glsl";
const GLchar* fragmentSource = R"glsl(
    #version 150 core
    uniform vec3 triangleColor;
    out vec4 outColor;
    void main()
    {
        outColor = vec4(triangleColor, 1.0);
    }
)glsl";

/* Private Function Declartations */
void error_callback(int error, const char* description);

Game::Game() {
    // Create the window for the game
}

Game::~Game() {}

void Game::run() {

    // fileHandler::FileHandler fh;
    // char path[] = "Shaders/vertex_shader.glsl";
    // std::string fileData;
    // fh.read_text_file(path, fileData);

    // std::cout << "FILE DATA: " << fileData << "\n";

    // return;

    if (glfwInit() != GLFW_TRUE) {
        std::cout << "GLFW could not be initialised" << std::endl;
        return;
    }

    window = glfwCreateWindow(640, 480, "Sequoia", NULL, NULL);
    if (window == NULL) {
        std::cout << "Window could not be created" << std::endl;
        glfwTerminate();
        return;
    }

    // Make the window's context current. This must happen before glew init
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW FAILED" << std::endl;
    }

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

    // Creating the VAO needs to be at the start of your program!!
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // // Create vertex buffer object. This
    GLuint vbo;
    glGenBuffers(1, &vbo); // Generate 1 buffer

    // Make the buffer that was just created active
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Adding data to buffer doesn't depend on the id of the buffer but which buffer
    // is currently active
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // // Create vertex shader object and add shader to vertices
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create fragment shader object and add shader to vertices
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Connect the vertex and fragment shader together so all the data
    // from the vertex shader goes to the fragment shader
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // glBindFragDataLocation(shaderProgram, 0, "outColor");

    // Linking the shader program required for connect to occur
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);

    /****** END CODE BLOCK ******/
    float count = 0.0f;

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

        count += 0.0001f;
        GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
        glUniform3f(uniColor, 1.0f, 0.0f, 0.0f);
        glUniform3f(uniColor, (sin(count * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

        frames++;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
}

void Game::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear screen to black
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3); // Draw triangle
}