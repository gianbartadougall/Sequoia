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
#include "objectLoader.h"
#include "array.h"

using namespace game;
using namespace std::chrono;
using namespace debugLog;
using namespace objectLoader;
using namespace object;

#define WINDOW_WIDTH  1000
#define WINDOW_HEIGHT 600

/* Private variable Declarations */
GLFWwindow* window;

// Shader sources
std::string vertexShaderPath   = "Shaders/mvertex_shader.glsl";
std::string fragmentShaderPath = "Shaders/fragment_shader.glsl";
std::string objectFilePath	   = "Resources/Objects/";

/* Private Function Declartations */

Game::Game() {
	// Create the window for the game

	if (glfwInit() != GLFW_TRUE) {
		DebugLog::log_error("GLFW could not be initialised");
		exit(1);
	}

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sequoia", NULL, NULL);
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
	const int numObjects		   = 1;
	string objectNames[numObjects] = {objectFilePath + "cube1.obj"};
	vector3f::Vector3f cubePosition(0, 0, 0);

	Object* objects = objLoader.load_objects(objectNames, numObjects);

	// ObjectData objects[numObjects];
	// for (int i = 0; i < numObjects; i++) {
	// 	objLoader.load_3D_object(objectFilePath + objectNames[i], &objects[i]);
	// }

	shaderLoader::ShaderLoader sl;
	GLuint shaderProgramId = sl.load_shader(vertexShaderPath, fragmentShaderPath);
	debugLog.log_message("Shader loaded");
	/****** START CODE BLOCK ******/
	// Description: Testing rendering

	vector3f::Vector3f translateC(0.0f, 0.0f, -1.0f);
	vector3f::Vector3f scaleC(0.2, 0.2, 0.2);
	vector4f::Vector4f rotateC(0.2, 1, 1, 0);

	vector3f::Vector3f translateP(0.0f, 0.0f, -1.0f);
	vector3f::Vector3f scaleP(0.3, 0.3, 0.3);
	vector4f::Vector4f rotateP(0.2, 1, 0, 0);

	matrix4f::Matrix4f projMat;
	projMat.projection_matrix(WINDOW_WIDTH, WINDOW_HEIGHT, 0.1, 10);
	GLint projectionMatrix = glGetUniformLocation(shaderProgramId, "projectionMatrix");
	glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projMat.m);

	projMat.print();

	matrix4f::Matrix4f transMat;
	transMat.scale(0.2);
	transMat.translate(0, 0, -5.0);
	GLint tranformationMatrix = glGetUniformLocation(shaderProgramId, "transformationMatrix");
	glUniformMatrix4fv(tranformationMatrix, 1, GL_FALSE, transMat.m);

	/****** END CODE BLOCK ******/
	float theta = 0;
	float phi	= 0;

	debugLog.log_message("Reached while loop 1");
	// Run main game loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {

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
			transMat.print();
		}
		// transMat.rotate(0.0001, 0, 0);
		transMat.translate(0, 0, 0.0001);

		// transMat.translate(0, 0, 0.0001);

		glUseProgram(shaderProgramId);
		glUniformMatrix4fv(tranformationMatrix, 1, GL_FALSE, transMat.m);

		frames++;
	}

	glfwTerminate();
}

void Game::render(Object* objects, int numObjects) {

	// Clear the screen to bloack
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // WHAT DOES THIS DO??

	for (int i = 0; i < numObjects; i++) {
		// TODO: Bind the vertex buffer as well so when there are multiple objects they will render correctly
		glBindBuffer(GL_ARRAY_BUFFER, objects->mesh->vbo);

		// Bind the element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects[i].mesh->ebo);
		// Draw the object
		glDrawElements(GL_TRIANGLES, objects[i].mesh->eboSize, GL_UNSIGNED_INT, 0); // Draw triangle
	}
}

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