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
#include <chrono> // Required for getting system time
#include <string>
#include <cmath>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>

/** GLEW Includes. This must be included before GLFW includes. GLEW must
 * be included before GLFW includes. Including GLEW before private includes
 * is also recommended to avoid header file conflicts
 */
#define GLEW_STATIC
#include <GL/glew.h>

/* GLFW Includes */
#include <GLFW/glfw3.h>

/* Personal Includes */
#include "game.h"
#include "debugLog.h"
#include "matrix4f.h"
#include "vector4f.h"
#include "objectLoader.h"
#include "array.h"
#include "gameSettings.h"
#include "baseShader.h"
#include "mathUtils.h"
#include "boundingBox.h"
#include "physicsSettings.h"
#include "collision.h"
#include "objectLoader.h"

using namespace game;
using namespace std::chrono;
using namespace debugLog;
using namespace objectLoader;
using namespace object;
using namespace baseShader;
using namespace boundingBox;
using namespace collision;

/* Private Marcos */
#define OBJECT(line)		  (line[0] == 'O')
#define VAO(line)			  (line[0] == 'V')
#define SHADER(line)		  (line[0] == 'S')
#define ENTITY(line)		  (line[0] == 'E')
#define CAMERA_SETTING(line)  (line[0] == 'C' && line[1] == 'S')
#define GRAVITY_SETTING(line) (line[0] == 'G' && line[1] == 'S')

/* Private variable Declarations */
GLFWwindow* window;

BaseShader shader;

// Shader sources
std::string TEST_GAME = "../Resources/Games/test_game.txt";

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

	// glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Game::~Game() {

	// Free all resources used
	delete objects;
	delete baseShaders;

	for (int i = 0; i < this->numShaders; i++) {
		glDeleteProgram(this->baseShaders[i].programId);
		glDeleteShader(this->baseShaders[i].vertexShaderId);
		glDeleteShader(this->baseShaders[i].fragmentShaderId);
	}

	// Free any resources that were used
	glfwTerminate();
}

void Game::run() {

	int frames					   = 0;
	system_clock::time_point time1 = system_clock::now();

	// Load everything in the game (only consists of objects at the moment)
	load_game(TEST_GAME);

	// int minLength = 1000000; // Theoretical minimum length. Arbitrary I just set it to a large number

	// Compute game stats
	for (int i = 0; i < numEntities; i++) {
		// if (this->objects[i].boundingBox.length() < minLength) {
		// 	minLength = this->objects[i].boundingBox.length();
		// }
		cout << "Entity " << i << endl;
		cout << "EBO Size " << objects[i].eboSize << endl;
	}

	// float minSectorSize = 8 * minLength * minLength * minLength;
	// cout << "Smallest volume: " << minSectorSize << endl;

	// Run main game loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {

		detect_keys();

		/* Update entities */
		// for (int i = 0; i < numEntities; i++) {
		// 	objects[i].update();
		// }

		// Collision::rigid_body_collision(&objects, numEntities);

		/* Render here */
		renderer.render_objects1(&camera, this->objects, this->numEntities);
		// renderer.render(this->vaos, numVaos, &camera, objects, objectListSizes);

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

		frames++;
	}

	glfwTerminate();
}

void Game::load_game(string filePath) {

	// Confirm given file path exists
	std::ifstream gameFile(filePath);

	if (gameFile.is_open() != true) {
		DebugLog::log_error("Could not load game. The file could not be read");
		cout << "Filepath: " << filePath << endl;
		return;
	}

	string line;
	while (getline(gameFile, line)) {

		if (ENTITY(line)) {
			this->numEntities++;
		}

		if (SHADER(line)) {
			this->numShaders++;
		}
	}

	// Go back to the start of the gameFile
	gameFile.clear();
	gameFile.seekg(0);

	this->objects	  = new Object[numEntities];
	this->baseShaders = new BaseShader[numShaders];
	string shaders[numShaders];

	int oi			   = 0;
	int si			   = 0;
	GLuint activeVao   = 0;
	int currentEboSize = 0;

	MeshBufferData currentMBD;

	// Load in all the entities in the game
	while (getline(gameFile, line)) {

		if (OBJECT(line)) {
			string data[3];
			StrUtils::split_string(line, data, 0, ',');
			int shaderIndex = atoi(data[1].c_str());
			objectLoader.new_object(data[2], &baseShaders[shaderIndex], &currentMBD);
			continue;
		}

		// The shader needs to be compiled after the VBO has been compiled otherwise it won't work!
		// You will need to fix this up for everything else
		if (SHADER(line)) {
			shaderLoader.load_baseshader(line, &baseShaders[si]);
			continue;
		}

		if (ENTITY(line)) {
			objects[oi].init(&currentMBD, line);
			objects[oi++].set_shader(&baseShaders[si]);
			continue;
		}

		if (GRAVITY_SETTING(line)) {
			phys.load_values(line);
			continue;
		}

		if (CAMERA_SETTING(line)) {
			this->camera.load_state(line);
			continue;
		}
	}
}

// void Game::load_game1(string filePath) {

// 	// Confirm given file path exists
// 	std::ifstream gameFile(filePath);

// 	if (gameFile.is_open() != true) {
// 		DebugLog.log_error("Could not load game. The file could not be read");
// 		cout << "Filepath: " << filePath << endl;
// 		return;
// 	}

// 	// Calculate the number of entities in the game

// 	string line;
// 	while (getline(gameFile, line)) {

// 		if (OBJECT(line)) {
// 			this->numVbos++;
// 		}

// 		if (SHADER(line)) {
// 			this->numShaders++;
// 		}

// 		if (VAO(line)) {
// 			this->numVaos++;
// 		}
// 	}

// 	// Go back to the start of the gameFile
// 	gameFile.clear();
// 	gameFile.seekg(0);

// 	// Creat list of entity objects

// 	this->objects		  = new Object[numEntities];
// 	this->baseShaders	  = new BaseShader[numShaders];
// 	this->vaos			  = new GLuint[numVaos];
// 	this->vbos			  = new GLuint[numVbos];
// 	this->ebos			  = new GLuint[numVbos];
// 	this->objectListSizes = new int[numVaos];

// 	// Set the number of
// 	for (int i = 0; i < numVaos; i++) {
// 		this->objectListSizes[i] = 0;
// 	}

// 	string shaders[numShaders];

// 	int objIndex = 0;
// 	int si		 = 0;
// 	int vaoi	 = 0;
// 	int vboi	 = 0;

// 	glGenVertexArrays(numVaos, this->vaos);

// 	// Load in all the entities in the game
// 	while (getline(gameFile, line)) {

// 		if (VAO(line)) {
// 			glBindVertexArray(this->vaos[vaoi]);
// 			vaoi++;
// 			continue;
// 		}

// 		if (OBJECT(line)) {
// 			ObjectLoader::load_mesh(this->vbos[vboi], this->vbos[vboi]);
// 			vboi++;
// 		}

// 		if (SHADER(line)) {
// 			shaders[si] = line;
// 			si++;
// 			continue;
// 		}

// 		if (ENTITY(line)) {
// 			this->objectListSizes[vaoi - 1]++;
// 			objects[objIndex].load(line);
// 			objects[objIndex].loadShaderId = si;
// 			objIndex++;
// 			continue;
// 		}

// 		if (GRAVITY_SETTING(line)) {
// 			phys.load_values(line);
// 			continue;
// 		}

// 		if (CAMERA_SETTING(line)) {
// 			this->camera.load_state(line);
// 			continue;
// 		}
// 	}

// 	// Load shaders. It is important that this is done after all the vbos and vaos have been generated
// 	for (int i = 0; i < numShaders; i++) {
// 		// Load the shader
// 		shaderLoader.load_baseshader(shaders[i], &baseShaders[i]);

// 		for (int j = 0; j < numEntities; j++) {
// 			if (objects[j].loadShaderId == i) {
// 				objects[j].load_shader(&baseShaders[i]);
// 			}
// 		}
// 	}

// 	gameFile.close();

// 	// Load all the physics settings into each entity
// 	for (int i = 0; i < numEntities; i++) {
// 		objects[i].load_physics_settings(&phys);
// 	}

// 	// Unbind vao
// 	glBindVertexArray(0);
// }

void Game::detect_mouse() {

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (xpos < 0 || ypos < 0 || xpos > WINDOW_WIDTH || ypos > WINDOW_HEIGHT) {
		return;
	}

	// Problem is that I have static acis. Maybe need to use quaternions for this? Might be far easier
	if (xpos < (WINDOW_WIDTH / 2)) {
		camera.rotate_left();
	}

	if (xpos > (WINDOW_WIDTH / 2)) {
		camera.rotate_right();
	}

	if (ypos < (WINDOW_HEIGHT / 2)) {
		camera.rotate_up();
	}

	if (ypos > (WINDOW_HEIGHT / 2)) {
		camera.rotate_down();
	}

	glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void Game::detect_keys() {

	detect_mouse();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		exit(1);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		// Move the camera to the left
		camera.move_left();
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		// Move the camera to the right
		camera.move_right();
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		// Move the camera forward
		camera.move_forward();
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		// Move the camera backward
		camera.move_backward();
	}
}