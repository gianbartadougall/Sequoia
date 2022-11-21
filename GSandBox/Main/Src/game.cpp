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

/** GLEW Includes. This must be included before GLFW includes. GLEW must
 * be included before GLFW includes. Including GLEW before private includes
 * is also recommended to avoid header file conflicts
 */
#define GLEW_STATIC
#include <GL/glew.h>

/* GLFW Includes */
#include <GLFW/glfw3.h>

/* Private Includes */
#include "game.h"
#include "shaderLoader.h"
#include "debugLog.h"
#include "matrix4f.h"
#include "vector4f.h"

using namespace game;
using namespace std::chrono;
using namespace debugLog;

/* Private variable Declarations */
GLFWwindow* window;

// Shader sources
std::string vertexShaderPath   = "Shaders/vertex_shader.glsl";
std::string fragmentShaderPath = "Shaders/fragment_shader.glsl";

/* Private Function Declartations */

Game::Game() {
	// Create the window for the game

	if (glfwInit() != GLFW_TRUE) {
		DebugLog::log_error("GLFW could not be initialised");
		exit(1);
	}

	window = glfwCreateWindow(640, 480, "Sequoia", NULL, NULL);
	if (window == NULL) {
		DebugLog::log_error("Window could not be created");
		exit(2);
	}

	// Make the window's context current. This must happen before glew init
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		DebugLog::log_error("GLEW could not be initialised");
	}
}

Game::~Game() {

	// Free any resources that were used

	glfwTerminate();
}

void Game::run() {

	shaderLoader::ShaderLoader sl;
	GLchar* vertexSource   = sl.load_shader(vertexShaderPath);
	GLchar* fragmentSource = sl.load_shader(fragmentShaderPath);

	int frames					   = 0;
	system_clock::time_point time1 = system_clock::now();

	/****** START CODE BLOCK ******/
	// Description: Testing rendering

	float vertices[] = {
		-0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // top left (x, y, z, r, g, b)
		0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 0.0f, // Top-right (x, y, z, r, g, b)
		0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom-right (x, y, z, r, g, b)
		-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f  // Bottom-left (x, y, z, r, g, b)
	};

	float tMat[16] = {
		1.0f, 0.0f, 0.0f, 0.0f, //
		0.0f, 1.0f, 0.0f, 0.0f, //
		0.0f, 0.0f, 1.0f, 0.0f, //
		0.0f, 0.0f, 0.0f, 1.0f	//
	};

	// vector4f::Vector4f translate(0, 0, 0);
	// vector4f::Vector4f scale(1, 1, 1);
	// vector4f::Vector4f rotate(0, 0, 0);
	// matrix4f::Matrix4f tMat(translate, scale, rotate);

	// Creating the VAO needs to be at the start of your program!!
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint tMatvao;
	glGenVertexArrays(1, &tMatvao);

	// // Create vertex buffer object. This
	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer

	// Create vbo for storing element data. This is means we can reuse vertices
	GLuint elements[] = {0, 1, 2, 2, 3, 0};
	GLuint ebo;
	glGenBuffers(1, &ebo);

	// Make the buffer that was just created active
	// Adding data to buffer doesn't depend on the id of the buffer but which buffer
	// is currently active
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint tMatvbo;
	glGenBuffers(1, &tMatvbo); // Generate 1 buffer

	glBindBuffer(GL_ARRAY_BUFFER, tMatvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tMat), tMat, GL_STATIC_DRAW);

	// // Create vertex shader object and add shader to vertices
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	int success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		DebugLog::log_error("Vertex shader failed to compile");
	}

	// Create fragment shader object and add shader to vertices
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		DebugLog::log_error("Fragment shader failed to compile");
	}

	// Connect the vertex and fragment shader together so all the data
	// from the vertex shader goes to the fragment shader
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColour");

	// Linking the shader program required for connect to occur
	glLinkProgram(shaderProgram);

	glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		DebugLog::log_error("Shader failed to link");
	}

	glUseProgram(shaderProgram);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

	// To make OpenGL take in the colour data we need to do the following
	GLint colAttrib = glGetAttribLocation(shaderProgram, "colour");
	glEnableVertexAttribArray(colAttrib);
	// The following code tells OpenGL where the colour values are in the matrix. second last parameter says
	// each vertex has 5 values and the last paramter says the col attribute starts at the 2nd index and goes for
	// three (specified by 2nd arg)
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	// Transformation matrix!!!

	glBindVertexArray(tMatvao);
	GLint transAttrib = glGetAttribLocation(shaderProgram, "transformation");
	glEnableVertexAttribArray(transAttrib);
	glVertexAttribPointer(transAttrib, 16, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), 0);

	// When Drawing multiple triangles, it is saves memory if you can reuse vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	/****** END CODE BLOCK ******/

	// Run main game loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {

		// tMat[3] += 0.0001f;
		// tMat[7] += 0.0001f;
		// tMat[11] += 0.0001f;

		/* Render here */
		render(tMat, tMatvbo);

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

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &tMatvbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
	glDeleteVertexArrays(1, &tMatvao);
	glfwTerminate();
}

void Game::render(float mat[16], GLuint vbo) {

	// To update variable in vertex/fragment shader
	// GLuint location = glGetUniformLocation(programHangle, "transformation");

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear screen to black
	glClear(GL_COLOR_BUFFER_BIT);

	// The last 3 args tell openGL about the element array
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw triangle
}