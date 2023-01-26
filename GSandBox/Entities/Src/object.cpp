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
#include "vector3f.h"
#include "vector3i.h"
#include "algorithms.h"
#include "boundingBox.h"

/* Private Macros */
#define VERTEX_DATA(line)	 (line[0] == 'v' && line[1] == ' ')
#define FACE_DATA(line)		 (line[0] == 'f' && line[1] == ' ')
#define REMOVE_COMMAND(line) (line[0] = 'f'; line[1] = ' ')

/* Private Enumerations and Structures */

using namespace object;
using namespace vector3f;
using namespace vector3i;
using namespace algorithms;
using namespace boundingBox;

Object::Object() {}

Object::~Object() {}

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

	Vector3f* vertices;
	Vector3i* vertexConnectionList;
	vertices			 = new Vector3f[numVertices];
	vertexConnectionList = new Vector3i[numFaces];
	int vi				 = 0;
	int vcli			 = 0;

	// Values for calculating bounding box. Setting values to reasonable min and max values
	// For super large objects, these may need to be adjust
	float minX = 1000000;
	float minY = 1000000;
	float minZ = 1000000;
	float maxX = -1000000;
	float maxY = -1000000;
	float maxZ = -1000000;

	// Store data into the arrays that were just created
	while (getline(objFile, line)) {

		if (VERTEX_DATA(line)) {
			string vertex[3];
			strUtils.split_string(line, vertex, 2, ' ');

			float vx = stof(vertex[0]);
			float vy = stof(vertex[1]);
			float vz = stof(vertex[2]);

			vertexData[vdi++] = vx;
			vertexData[vdi++] = vy;
			vertexData[vdi++] = vz;

			// Test code here
			vertices[vi].set(vx, vy, vz);
			vi++;
			// Test code here

			// Adding a default colour to the objects for the moment
			vertexData[vdi++] = 0.5;
			vertexData[vdi++] = 0.5;
			vertexData[vdi++] = 0.5;

			// CODE FOR CALCULATING THE BOUNDING BOX
			if (vx < minX) {
				minX = vx;
			}
			if (vy < minY) {
				minY = vy;
			}
			if (vz < minZ) {
				minZ = vz;
			}

			if (vx > maxX) {
				maxX = vx;
			}
			if (vy > maxY) {
				maxY = vy;
			}
			if (vz > maxZ) {
				maxZ = vz;
			}

			// CODE FOR CALCULATING THE BOUNDING BOX
		}

		if (FACE_DATA(line)) {

			string edges[3];
			strUtils.split_string(line, edges, 2, ' ');

			// Loop through each split to extract the element data
			for (int i = 0; i < 3; i++) {

				string faceData[3];
				strUtils.split_string(edges[i], faceData, 0, '/');
				elementData[edi++] = stoi(faceData[0]) - 1;

				// test code
				if (i == 0) {
					vertexConnectionList[vcli].set_x(stoi(faceData[0]) - 1);
				} else if (i == 1) {
					vertexConnectionList[vcli].set_y(stoi(faceData[0]) - 1);
				} else {
					vertexConnectionList[vcli].set_z(stoi(faceData[0]) - 1);
				}
				// test code
			}

			// test code
			vcli++;
			// test code
		}
	}

	// Compute the volume
	entity->volume = Algorithms::compute_volume(vertices, vertexConnectionList, numFaces);
	cout << minX << " " << minX << " " << minY << " " << minZ << " " << maxX << " " << maxY << " " << maxZ << " "
		 << endl;
	entity->boundingBox.set(minX, minY, minZ, maxX, maxY, maxZ);

	// entity->boundingBox[0].set(minX, minY, minZ);
	// entity->boundingBox[1].set(minX, minY, maxZ);
	// entity->boundingBox[2].set(minX, maxY, minZ);
	// entity->boundingBox[3].set(minX, maxY, maxZ);
	// entity->boundingBox[4].set(maxX, minY, minZ);
	// entity->boundingBox[5].set(maxX, minY, maxZ);
	// entity->boundingBox[6].set(maxX, maxY, minZ);
	// entity->boundingBox[7].set(maxX, maxY, maxZ);

	// Creating the faces of the bounding boxes. Each vector contains
	// three indexes which correspond to vertecies in the bounding
	// box array
	// entity->boundingBoxFaces[0].set(0, 4, 2); // Face 0
	// entity->boundingBoxFaces[0].set(4, 7, 6); // Face 1
	// entity->boundingBoxFaces[0].set(7, 3, 5); // Face 2
	// entity->boundingBoxFaces[0].set(3, 0, 2); // Face 3
	// entity->boundingBoxFaces[0].set(0, 4, 5); // Face 4
	// entity->boundingBoxFaces[0].set(2, 6, 7); // Face 5

	// Bind the vbo for this mesh to make them active
	glBindBuffer(GL_ARRAY_BUFFER, entity->vbo);

	// Store vertex data into the current active vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// Bind the element buffer for this object to make it active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entity->ebo);
	// Store element data into the current active element buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData, GL_STATIC_DRAW);
}