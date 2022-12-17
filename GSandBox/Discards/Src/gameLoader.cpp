/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for gameLoader
 * @version 0.1
 * @date Sat Dec 17 20:32:36 2022

 *
 * @copyright Copyright (c)
 *
 */

/* Public Includes */
#include <iostream>
#include <fstream>
#include <sstream>

/* GLEW Includes */

/* Private Includes */
#include "gameLoader.h"

/* Private Macros */
#define OBJECT(line) (line[0] == 'O')
#define SHADER(line) (line[0] == 'S')
#define VAO(line)	 (line[0] == 'V')

/* Private Enumerations and Structures */

using namespace gameLoader;

GameLoader::GameLoader() {}

GameLoader::~GameLoader() {}

uint8_t GameLoader::search_game_parameters(string filePath) {

	// Confirm given file path exists
	std::ifstream gameFile(filePath);

	if (gameFile.is_open() != true) {
		log.log_error("Could not load game. The file could not be read");
		cout << "Filepath: " << filePath << endl;
		return 1;
	}

	// Calculate the number of entities in the game

	string line;
	while (getline(gameFile, line)) {

		if (OBJECT(line)) {
			this->numObjects++;
		}

		if (SHADER(line)) {
			this->numShaders++;
		}

		if (VAO(line)) {
			this->numVaos++;
		}
	}

	gameFile.close();
}

void GameLoader::load_game(string filePath) {

	ShaderLoader shaderLoader;

	// Find all the game paramters
	if (search_game_parameters != 0) {
		return;
	}

	// Creat list of entity objects

	this->objects		  = new Object[numEntities];
	this->baseShaders	  = new BaseShader[numShaders];
	this->vaos			  = new GLuint[numVaos];
	this->objectListSizes = new GLuint[numVaos];

	for (int i = 0; i < numVaos; i++) {
		this->objectListSizes[i] = 0;
	}

	string shaders[numShaders];
	int objectShaderIds[numShaders];

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
			cout << "Num shaders: " << numShaders << "si: " << si << " line: " << line << endl;
			shaders[si] = line;
			cout << "after" << endl;
			si++;
			continue;
		}

		if (OBJECT(line)) {
			this->objectListSizes[vi - 1]++;
			// Load the entity. Subtract 1 from shader index because shader index
			// is always pointer to the next shader to load
			// objects[objIndex].load(line, &baseShaders[si - 1]);
			objects[objIndex].load(line);
			objectShaderIds[objIndex] = si - 1;
			log.log_warning("Finsihed loading");
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
				objects[j].load_shader(&baseShaders[i]);
			}
		}
	}

	cout << "Num VAOS: " << numVaos << endl;
	for (int i = 0; i < numVaos; i++) {
		cout << "OS: " << this->objectListSizes[i] << endl;
	}
}