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
using namespace objectLoader;

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

	window = glfwCreateWindow(620, 480, "Sequoia", NULL, NULL);
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

	int frames					   = 0;
	system_clock::time_point time1 = system_clock::now();

	objectLoader::ObjectLoader objLoader;
	ObjectData objects[1];
	objLoader.load_3D_object("Resources/Objects/cube1.obj", &objects[0]);

	shaderLoader::ShaderLoader sl;
	GLuint shaderProgramId = sl.load_shader(vertexShaderPath, fragmentShaderPath);

	/****** START CODE BLOCK ******/
	// Description: Testing rendering

	vector3f::Vector3f translate(0.0f, 0.0f, 0.0f);
	vector3f::Vector3f scale(0.5, 0.5, 0.5);
	vector4f::Vector4f rotate(10, 1, 1, 0);

	sl.load_vertex_shader_attributes(shaderProgramId, translate, scale, rotate);

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
		render(objects, 1);

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
		}

		rotate.add(0.00001, 0, 0, 0);

		sl.load_vertex_shader_attributes(shaderProgramId, translate, scale, rotate);

		frames++;
	}

	glfwTerminate();
}

void Game::render(ObjectData* objects, int numObjects) {

	// Clear the screen to bloack
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // WHAT DOES THIS DO??

	for (int i = 0; i < numObjects; i++) {
		// TODO: Bind the vertex buffer as well so when there are multiple objects they will render correctly

		// Bind the element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects[i].elementBuffer);
		// Draw the object
		glDrawElements(GL_TRIANGLES, objects[i].elementArraySize, GL_UNSIGNED_INT, 0); // Draw triangle
	}
}