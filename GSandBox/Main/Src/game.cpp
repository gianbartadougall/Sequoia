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
#include <windows.h>

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
std::string vertexShaderPath   = "Shaders/qvertex_shader.glsl";
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

	// matrix4f::Matrix4f m2(1, 3, 4, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
	// matrix4f::Matrix4f m1(2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3);

	// m2.multiply(&m1);
	// m2.print();

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

	// float tMatf[16] = {
	// 	1.0f, 0.0f, 0.0f, 0.2f, //
	// 	0.0f, 1.0f, 0.0f, 0.2f, //
	// 	0.0f, 0.0f, 1.0f, 0.2f, //
	// 	0.0f, 0.0f, 0.0f, 1.0f	//
	// };

	// Creating the VAO needs to be at the start of your program!!
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

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

	vector4f::Vector4f translate1(0.0f, 0.0f, 0.0f);
	vector4f::Vector4f scale1(1, 1, 1);
	vector4f::Vector4f rotate1(10, 0, 0);
	matrix4f::Matrix4f tMat(translate1, scale1, rotate1);
	tMat.print();

	matrix4f::Matrix4f rotx;
	matrix4f::Matrix4f roty;
	matrix4f::Matrix4f rotz;
	// matrix4f::Matrix4f qrotx;
	// matrix4f::Matrix4f qroty;
	// matrix4f::Matrix4f qrotz;
	rotx.rotatex(0.0001f);
	roty.rotatey(0.0001f);
	rotz.rotatez(0.0001f);
	rotx.multiply(&roty);
	rotx.multiply(&rotz);

	// qrotx.qrotx(0.001f);
	// qroty.qroty(0.0001f);
	// qrotz.qrotz(0.00001f);

	// Transformation matrix!!!
	GLint uniTrans = glGetUniformLocation(shaderProgram, "transformation");
	glUniformMatrix4fv(uniTrans, 1, GL_TRUE, tMat.m);

	float theta		 = 0.5f;
	GLint floatTrans = glGetUniformLocation(shaderProgram, "theta");
	glUniform1f(floatTrans, theta);

	float scale[3]	 = {1, 1, 1};
	GLint scaleTrans = glGetUniformLocation(shaderProgram, "scale");
	glUniform3fv(scaleTrans, 1, scale);

	float translate[3]	 = {0, 0, 0};
	GLint translateTrans = glGetUniformLocation(shaderProgram, "translation");
	glUniform3fv(translateTrans, 1, translate);

	// When Drawing multiple triangles, it is saves memory if you can reuse vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	/****** END CODE BLOCK ******/

	float sd = 1;
	float td = 1;

	// Run main game loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		// Handle key presses
		// if (GetKeyState('A') & 0x8000) {
		// 	// Move the object to the left
		// 	translate.set(-distance, 0, 0);
		// 	tMat.transform(translate, scale, rotate);
		// 	tMat.print();
		// 	translate.set(0, 0, 0);
		// }

		// if (GetKeyState('D') & 0x8000) {
		// 	// Move the object to the left
		// 	translate.set(distance, 0, 0);
		// 	tMat.transform(translate, scale, rotate);
		// 	tMat.print();
		// 	translate.set(0, 0, 0);
		// }

		// if (GetKeyState('W') & 0x8000) {
		// 	// Move the object to the left
		// 	scale.set(1.01f, 1.01f, 1.01f);
		// 	tMat.transform(translate, scale, rotate);
		// 	tMat.print();
		// 	scale.set(1, 1, 1);
		// }

		// if (GetKeyState('S') & 0x8000) {
		// 	// Move the object to the left
		// 	scale.set(0.99f, 0.99f, 0.99f);
		// 	tMat.transform(translate, scale, rotate);
		// 	tMat.print();
		// 	scale.set(1, 1, 1);
		// }

		/* Render here */
		render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		// Print the FPS
		auto elapsedTime = duration_cast<milliseconds>(system_clock::now() - time1);
		if (elapsedTime.count() >= 1000) {
			// std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			time1  = system_clock::now();
			// tMat.print();
		}
		// glUniform1f(floatTrans, theta);
		// tMat.multiply(&qrotx);
		// tMat.multiply(&qroty);
		// tMat.multiply(&qrotz);
		// tMat.multiply(&rotx);
		// tMat.multiply(&roty);
		// tMat.multiply(&rotz);

		theta += 0.0001f;
		translate[0] += td * 0.00001f;
		translate[1] += td * 0.00001f;
		translate[2] += td * 0.00001f;
		scale[0] += sd * 0.00001f;
		scale[1] += sd * 0.00001f;
		scale[2] += sd * 0.00001f;

		if (translate[0] > 0.8) {
			td = -1;
		} else if (translate[0] < -0.8) {
			td = 1;
		}

		if (scale[0] > 1.3) {
			sd = -1;
		} else if (scale[0] < 0.7) {
			sd = 1;
		}

		glUniform1f(floatTrans, theta);
		glUniform3fv(scaleTrans, 1, scale);
		glUniform3fv(translateTrans, 1, translate);

		// glUniformMatrix4fv(uniTrans, 1, GL_TRUE, tMat.m);

		frames++;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
	glfwTerminate();
}

void Game::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Clear screen to black
	glClear(GL_COLOR_BUFFER_BIT);

	// The last 3 args tell openGL about the element array
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw triangle
}