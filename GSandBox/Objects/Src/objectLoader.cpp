/**
 * @file objectLoader.cpp
 * @author Gian Barta-Dougall
 * @brief System file for objectLoader
 * @version 0.1
 * @date --
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
#include "objectLoader.h"
#include "array.h"

/* Private Macros */
#define VERTEX_DATA(line)	 (line[0] == 'v' && line[1] == ' ')
#define FACE_DATA(line)		 (line[0] == 'f' && line[1] == ' ')
#define REMOVE_COMMAND(line) (line[0] = 'f'; line[1] = ' ')

using namespace objectLoader;
using namespace array;

ObjectLoader::ObjectLoader() {
	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Only one object to create
	glGenBuffers(MAX_NUM_OBJECTS, vba);
	glGenBuffers(MAX_NUM_OBJECTS, eba);
}

ObjectLoader::~ObjectLoader() {

	// Delete all the vertex buffer objects
	glDeleteBuffers(MAX_NUM_OBJECTS, vba);

	// Delete all the element buffer objects
	glDeleteBuffers(MAX_NUM_OBJECTS, eba);

	glDeleteVertexArrays(1, &vao);
}

void ObjectLoader::load_3D_object(string objFilePath, ObjectData* objectData) {

	if (objectIndex == MAX_NUM_OBJECTS) {
		debugLog.log_error("Maximum number of objects already loaded. Please increase size to load more!");
		return;
	}

	// Confirm given file path exists
	std::ifstream textFile(objFilePath);

	if (textFile.is_open() != true) {
		debugLog.log_error("Unable to load 3D object");
		// std::cout << "Unable to open '" << filePath << "'\n";
		return;
	}

	int numVertices = 0;
	int numFaces	= 0;
	string line;

	// Calculate the number of vertices and faces the object has
	while (getline(textFile, line)) {

		if (VERTEX_DATA(line)) {
			numVertices++;
		}

		if (FACE_DATA(line)) {
			numFaces++;
		}
	}

	// Go back to the start of the textfile
	textFile.clear();
	textFile.seekg(0);

	/****** START CODE BLOCK ******/
	// Description: // Create arrays and array indexs for each type of data to be extracted

	// List for all vertecies of object. Multiply by 6 because V = x, y, z, r, g, b
	float vertexData[numVertices * 6];
	int vdi = 0;

	// List of elements so OpenGL knows which order the vertecies should be connected
	int elementData[numFaces * 3];
	int edi = 0;

	/****** END CODE BLOCK ******/

	// Store data into the arrays that were just created
	while (getline(textFile, line)) {

		if (VERTEX_DATA(line)) {
			string vertices[3];
			split_triplet(line, vertices, 2, ' ');
			vertexData[vdi++] = stof(vertices[0]);
			vertexData[vdi++] = stof(vertices[1]);
			vertexData[vdi++] = stof(vertices[2]);
			vertexData[vdi++] = 0.55f;
			vertexData[vdi++] = 0.55f;
			vertexData[vdi++] = 0.55f;
		}

		if (FACE_DATA(line)) {

			string faces[3];
			split_triplet(line, faces, 2, ' ');

			// Loop through each split to extract the element data
			for (int i = 0; i < 3; i++) {

				string faceData[3];
				split_triplet(faces[i], faceData, 0, '/');
				elementData[edi++] = stoi(faceData[0]) - 1;
			}
		}
	}

	// Bind the vertex buffer for this object to make it active
	glBindBuffer(GL_ARRAY_BUFFER, vba[objectIndex]);
	// Store vertex data into the current active vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// Bind the element buffer for this object to make it active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eba[objectIndex]);
	// Store element data into the current active element buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData, GL_STATIC_DRAW);

	// Copy object data to struct
	objectData->elementBuffer	 = eba[objectIndex];
	objectData->elementArraySize = numFaces * 3;

	objectIndex++;
}

/**
 * @brief Splits a line containing three pieces of data all seperated by a common delimiter.
 * E.g
 * 		string line = "data = 0 2 4"
 * 		string results[3];
 *
 * 		// Because the delimiter is a space and there are other spaces in the input string,
 * 		// the start index specifies what index the function will start splitting up data
 * 		split_triplet(line, results, 6, ' ');
 *
 * This code will output
 * 		results[0] = "0"
 * 		results[1] = "2"
 * 		results[2] = "4"
 *
 * @param line The string containing the triplet of data to be split
 * @param splitList An empty list of type string with a length of 3. The split data will be
 * saved into this list
 * @param start The index this function will start searching for delimiters
 * @param delimiter The char the function will split the data on
 */
void ObjectLoader::split_triplet(string line, string* splitList, int start, char delimiter) {
	int index = 0;
	for (int i = start; true; i++) {

		if (line[i] == delimiter) {
			splitList[index++] = line.substr(start, i - start);
			start			   = i + 1;
		}

		if (line[i] == '\0') {
			splitList[index++] = line.substr(start, i - start);
			break;
		}
	}
}