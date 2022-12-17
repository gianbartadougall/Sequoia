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

/* Private Includes */
#include "game.h"
#include "shaderLoader.h"
#include "debugLog.h"
#include "matrix4f.h"
#include "vector4f.h"
#include "objectLoader.h"
#include "array.h"
#include "gameSettings.h"
#include "baseShader.h"

using namespace game;
using namespace std::chrono;
using namespace debugLog;
using namespace objectLoader;
using namespace object;
using namespace shaderLoader;
using namespace baseShader;

/* Private Marcos */
#define OBJECT(line) (line[0] == 'O')
#define SHADER(line) (line[0] == 'S')
#define VAO(line)	 (line[0] == 'V')

/* Private variable Declarations */
GLFWwindow* window;

BaseShader shader;

// Shader sources
std::string vertexShaderPath   = "Shaders/mvertex_shader.glsl";
std::string fragmentShaderPath = "Shaders/fragment_shader.glsl";
std::string TEST_GAME		   = "../Resources/Games/test_game.txt";

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

	// Free any resources that were used
	glfwTerminate();
}

void Game::run() {

	int frames					   = 0;
	system_clock::time_point time1 = system_clock::now();

	// Load everything in the game (only consists of objects at the moment)
	load_game(TEST_GAME);

	// shaderLoader::ShaderLoader sl;
	// sl.load_baseshader("S,Shaders/mvertex_shader.glsl,Shaders/fragment_shader.glsl", &shader);
	// glUseProgram(shader.programId);
	// GLuint programId = sl.load_shader(vertexShaderPath, fragmentShaderPath);
	/****** START CODE BLOCK ******/
	// Description: Loading the projection matrix into the vertex shader. This only needs to be done once at the
	// start because the projection matrix should never need to change

	// matrix4f::Matrix4f projMat;
	// projMat.projection_matrix(WINDOW_WIDTH, WINDOW_HEIGHT, 0.1, 10);
	// GLint projectionMatrix = glGetUniformLocation(this->objects[0].shader->programId, "projectionMatrix");
	// glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, projMat.m);

	/****** END CODE BLOCK ******/

	for (int i = 0; i < this->numEntities; i++) {
		cout << "vbo: " << this->objects[i].vbo << endl;
		cout << "ebo: " << this->objects[i].ebo << endl;
	}

	// Run main game loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {

		detect_keys();

		/* Render here */
		renderer.render(this->vaos, numVaos, &camera, objects, objectListSizes);
		// render(this->objects);

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

		/****** START CODE BLOCK ******/
		// Description: Manipulate the orientation, position and scale of the objects in the scene
		for (int i = 0; i < this->numEntities; i++) {
			objects[i].rotation.add(0.000, 0.0001, 0.000);
		}

		/****** END CODE BLOCK ******/
		frames++;
	}

	glfwTerminate();
}

void Game::render(Object* objects) {

	// Clear the screen to bloack
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // WHAT DOES THIS DO??

	// All the objects use the same shader program for the moment
	GLuint programId;
	if (this->numEntities > 0) {
		programId = objects[0].shader->programId;
		glUseProgram(programId);
	}

	for (int i = 0; i < this->numEntities; i++) {

		if (objects[i].shader->programId != programId) {
			programId = objects[i].shader->programId;
			glUseProgram(programId);
		}

		// Update the uniforms so the correct values are loaded in the shaders for this object

		// Create transformation matrix. The rotation and scale must preceed the translation otherwise the resultant
		// matrix will distort the object because scale and rotating must happen when the object is at(0, 0, 0)
		matrix4f::Matrix4f tMat;
		tMat.scale(objects[i].scale);
		tMat.rotate(objects[i].rotation);
		tMat.translate(objects[i].position);
		glUniformMatrix4fv(5, 1, GL_FALSE, tMat.m);

		matrix4f::Matrix4f vMat;
		vMat.rotate(this->camera.rotation);
		vMat.translate(this->camera.position);
		glUniformMatrix4fv(1, 1, GL_FALSE, vMat.m);

		// glBindVertexArray(this->vao);
		glBindBuffer(GL_ARRAY_BUFFER, objects[i].vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects[i].ebo);
		glDrawElements(GL_TRIANGLES, objects[i].eboSize, GL_UNSIGNED_INT, 0); // Draw triangle
	}
}

void Game::load_game(string filePath) {

	ShaderLoader shaderLoader;

	// Confirm given file path exists
	std::ifstream gameFile(filePath);

	if (gameFile.is_open() != true) {
		log.log_error("Could not load game. The file could not be read");
		cout << "Filepath: " << filePath << endl;
		return;
	}

	// Calculate the number of entities in the game

	string line;
	while (getline(gameFile, line)) {

		if (OBJECT(line)) {
			this->numEntities++;
		}

		if (SHADER(line)) {
			this->numShaders++;
		}

		if (VAO(line)) {
			this->numVaos++;
		}
	}

	// Go back to the start of the gameFile
	gameFile.clear();
	gameFile.seekg(0);

	// Creat list of entity objects

	this->objects		  = new Object[numEntities];
	this->baseShaders	  = new BaseShader[numShaders];
	this->vaos			  = new GLuint[numVaos];
	this->objectListSizes = new int[numVaos];

	for (int i = 0; i < numVaos; i++) {
		this->objectListSizes[i] = 0;
	}

	string shaders[numShaders];
	int objectShaderIds[numEntities];

	int objIndex = 0;
	int si		 = 0;
	int vi		 = 0;

	glGenVertexArrays(numVaos, this->vaos);

	// Load in all the entities in the game
	while (getline(gameFile, line)) {

		if (VAO(line)) {
			glBindVertexArray(this->vaos[vi]);
			vi++;
		}

		if (SHADER(line)) {
			log.log_warning("here");
			shaders[si] = line;
			log.log_warning("here 2");
			si++;
			continue;
		}

		if (OBJECT(line)) {
			this->objectListSizes[vi - 1]++;
			// objects[objIndex].load(line, &baseShaders[si - 1]);
			objects[objIndex].load(line);
			objectShaderIds[objIndex] = si;
			objIndex++;
			continue;
		}
	}

	log.log_message("Got here");

	// Load shaders. It is important that this is done after all the vbos and vaos have been generated
	for (int i = 0; i < numShaders; i++) {
		// Load the shader
		shaderLoader.load_baseshader(shaders[i], &baseShaders[i]);

		for (int j = 0; j < numEntities; j++) {
			if (objects[j].loadShaderId == i) {
				log.log_message("Loading shader");
				objects[j].load_shader(&baseShaders[i]);
				log.log_message("loaded shader");
				baseShaders[i].print();
			}
		}
	}
}

void Game::detect_mouse() {

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (xpos < 0 || ypos < 0 || xpos > WINDOW_WIDTH || ypos > WINDOW_HEIGHT) {
		return;
	}

	if (xpos < (WINDOW_WIDTH / 2)) {
		camera.rotation.add(0, 0.001, 0);
	}

	if (xpos > (WINDOW_WIDTH / 2)) {
		camera.rotation.add(0, -0.001, 0);
	}

	if (ypos < (WINDOW_HEIGHT / 2)) {
		camera.rotation.add(0.001, 0, 0);
	}

	if (ypos > (WINDOW_HEIGHT / 2)) {
		camera.rotation.add(-0.001, 0, 0);
	}

	glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void Game::detect_keys() {

	detect_mouse();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		// Move the camera to the left
		camera.position.add(0.001, 0, 0);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		// Move the camera to the right
		camera.position.add(-0.001, 0, 0);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		// Move the camera forward
		camera.position.add(0, 0, 0.001);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		// Move the camera backward
		camera.position.add(0, 0, -0.001);
	}
}