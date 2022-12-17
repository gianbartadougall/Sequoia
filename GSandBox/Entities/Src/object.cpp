/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for object
 * @version 0.1
 * @date Sun Nov 27 20:31:08 2022

 *
 * @copyright Copyright (c)
 *
 */

/* Public Includes */
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

/* GLEW Includes */

/* Private Includes */
#include "object.h"

/* Private Macros */
#define VERTEX_DATA(line)	 (line[0] == 'v' && line[1] == ' ')
#define FACE_DATA(line)		 (line[0] == 'f' && line[1] == ' ')
#define REMOVE_COMMAND(line) (line[0] = 'f'; line[1] = ' ')

/* Private Enumerations and Structures */

using namespace object;

Object::Object() {}

Object::~Object() {}

/****** START CODE BLOCK ******/
// Description: TEMP CODE FOR TESTING
void Object::load(string objectData) {

	// Objects are stored in following format O,shaderId,filePath,xPos,yPos,zPos,xRot,yRot,zRot,xScl,yScl,zScl
	// Split the string by delimiter to extract data

	string data[12];
	strUtils.split_string(objectData, data, 0, ',');

	// Load the object
	const int i		   = 1;
	this->loadShaderId = atoi(data[i].c_str());
	cout << "loading model: ../Resources/Models/" << data[i + 1] << endl;
	load_mesh("../Resources/Models/" + data[i + 1], this);

	// Set the initial position of this object
	this->position.set(stof(data[i + 2]), stof(data[i + 3]), stof(data[i + 4]));
	this->rotation.set(stof(data[i + 5]), stof(data[i + 6]), stof(data[i + 7]));
	this->scale.set(stof(data[i + 8]), stof(data[i + 9]), stof(data[i + 10]));
}

/****** END CODE BLOCK ******/

void Object::load(string objectData, BaseShader* shader) {

	// Objects are stored in following format O,filePath,sid,xPos,yPos,zPos,xRot,yRot,zRot,xScl,yScl,zScl
	// Split the string by delimiter to extract data

	string data[11];
	strUtils.split_string(objectData, data, 0, ',');

	// Load the object
	cout << "loading model: ../Resources/Models/" << data[1] << endl;
	load_mesh("../Resources/Models/" + data[1], this);

	// Assign a pointer to the shader
	this->shader = shader;

	// Set the initial position of this object
	this->position.set(stof(data[2]), stof(data[3]), stof(data[4]));
	this->rotation.set(stof(data[5]), stof(data[6]), stof(data[7]));
	this->scale.set(stof(data[8]), stof(data[9]), stof(data[10]));
}

void Object::load_mesh(string filePath, Entity* entity) {

	// Confirm given file path exists
	std::ifstream objFile(filePath);

	if (objFile.is_open() != true) {
		log.log_error("Could not open file to load 3D object");
		cout << filePath << endl;
		return;
	}

	int numVertices = 0;
	int numFaces	= 0;
	string line;

	// Calculate the number of vertices and faces the object has
	while (getline(objFile, line)) {

		if (VERTEX_DATA(line)) {
			numVertices++;
		}

		if (FACE_DATA(line)) {
			numFaces++;
		}
	}

	// Go back to the start of the objFile
	objFile.clear();
	objFile.seekg(0);

	/****** START CODE BLOCK ******/
	// Description: // Create arrays and array indexs for each type of data to be extracted

	// List for all vertecies of object. Multiply by 6 because V = x, y, z, r, g, b
	float vertexData[numVertices * 6];
	int vdi = 0;

	// List of elements so OpenGL knows which order the vertecies should be connected
	entity->eboSize = numFaces * 3;
	int elementData[entity->eboSize];
	int edi = 0;

	/****** END CODE BLOCK ******/

	// Store data into the arrays that were just created
	while (getline(objFile, line)) {

		if (VERTEX_DATA(line)) {
			string vertices[3];
			strUtils.split_string(line, vertices, 2, ' ');
			vertexData[vdi++] = stof(vertices[0]);
			vertexData[vdi++] = stof(vertices[1]);
			vertexData[vdi++] = stof(vertices[2]);

			// Adding a default colour to the objects for the moment
			vertexData[vdi++] = 0.5;
			vertexData[vdi++] = 0.5;
			vertexData[vdi++] = 0.5;
		}

		if (FACE_DATA(line)) {

			string faces[3];
			strUtils.split_string(line, faces, 2, ' ');

			// Loop through each split to extract the element data
			for (int i = 0; i < 3; i++) {

				string faceData[3];
				strUtils.split_string(faces[i], faceData, 0, '/');
				elementData[edi++] = stoi(faceData[0]) - 1;
			}
		}
	}

	// Bind the vbo for this mesh to make them active
	glBindBuffer(GL_ARRAY_BUFFER, entity->vbo);

	/**
	 * @param1: The vao these settings will be saved in
	 * @param2: The number of components per vertex. Using 3D graphics => each vertex has x,y,z components
	 * @param3: The data type of each component in the vbo
	 * @param4: Whether the data should be normalised or not -> NOT ACTUALLY SURE WHAT THIS MEANS
	 * @param5: The number of data points associated to each vertex. Each vertex has an x,y,z location and a r,g,b
	 * colour
	 * @param6: The offset of when to start reading the data from the vbo
	 */
	// glVertexAttribPointer(this->vao, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), 0);
	// glBindAttribLocation(shaderProgram, this->vao, "position");

	// Store vertex data into the current active vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// Bind the element buffer for this object to make it active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo);
	// Store element data into the current active element buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData, GL_STATIC_DRAW);

	log.log_message("Finished loading object");
}