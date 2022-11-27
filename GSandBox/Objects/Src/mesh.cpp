/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for mesh
 * @version 0.1
 * @date Sun Nov 27 20:34:58 2022

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
#include "mesh.h"
#include "array.h"

/* Private Macros */
#define VERTEX_DATA(line)	 (line[0] == 'v' && line[1] == ' ')
#define FACE_DATA(line)		 (line[0] == 'f' && line[1] == ' ')
#define REMOVE_COMMAND(line) (line[0] = 'f'; line[1] = ' ')

/* Private Enumerations and Structures */

using namespace mesh;
using namespace vector3f;

Mesh::Mesh(GLuint vboId, GLuint eboId) {
	vbo = vboId;
	ebo = eboId;
}

Mesh::~Mesh() {}

void Mesh::load_mesh(string objectFilePath, Vector3f colour) {

	// Confirm given file path exists
	std::ifstream objFile(objectFilePath);

	if (objFile.is_open() != true) {
		log.log_error("Could not open file to load 3D object");
		cout << objectFilePath << endl;
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
	this->eboSize = numFaces * 3;
	int elementData[this->eboSize];
	int edi = 0;

	/****** END CODE BLOCK ******/

	array::Array array;
	// Store data into the arrays that were just created
	while (getline(objFile, line)) {

		if (VERTEX_DATA(line)) {
			string vertices[3];
			split_triplet(line, vertices, 2, ' ');
			vertexData[vdi++] = stof(vertices[0]);
			vertexData[vdi++] = stof(vertices[1]);
			vertexData[vdi++] = stof(vertices[2]);

			// Adding a default colour to the objects for the moment
			vertexData[vdi++] = colour.v[0];
			vertexData[vdi++] = colour.v[1];
			vertexData[vdi++] = colour.v[2];
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
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	// Store vertex data into the current active vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// Bind the element buffer for this object to make it active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	// Store element data into the current active element buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData, GL_STATIC_DRAW);
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
void Mesh::split_triplet(string line, string* splitList, int start, char delimiter) {
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