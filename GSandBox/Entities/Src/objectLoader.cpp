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
#include "strUtils.h"
#include "vector3f.h"
#include "vector3i.h"

/* Private Macros */
#define VERTEX_DATA(line)	 (line[0] == 'v' && line[1] == ' ')
#define FACE_DATA(line)		 (line[0] == 'f' && line[1] == ' ')
#define REMOVE_COMMAND(line) (line[0] = 'f'; line[1] = ' ')

using namespace objectLoader;
using namespace array;
using namespace vector3f;
using namespace vector3i;
using namespace strUtils;

ObjectLoader::ObjectLoader() {}

ObjectLoader::~ObjectLoader() {

	// // Delete vertex buffer objects
	// glDeleteBuffers(this->numObjects, this->vba);

	// // Delete element buffer objects
	// glDeleteBuffers(this->numObjects, this->eba);

	// // Delete all the vertex array objects
	// glDeleteVertexArrays(1, &vao);
}

GLuint ObjectLoader::new_vao() {

	// if (this->numVaos >= MAX_MESH_TYPES) {
	// 	DebugLog::log_error("Max number of VAOS reached!");
	// 	return 0;
	// }

	// this->numVaos++;
	// glGenVertexArrays(1, &this->vaos[this->numVaos]);

	// return this->numVaos;
}

void ObjectLoader::new_object(string filePath, BaseShader* baseShader, MeshBufferData* mbd) {

	// Confirm given file path exists
	std::ifstream objFile("../Resources/Models/" + filePath);

	if (objFile.is_open() != true) {
		DebugLog::log_error("Could not open file to load 3D object");
		cout << filePath << endl;
		return;
	}

	if (this->numMeshes >= MAX_MESHES) {
		DebugLog::log_error("Max number of VBOS reached!");
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
	int eboSize = numFaces * 3;
	int elementData[eboSize];
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
			StrUtils::split_string(line, vertex, 2, ' ');

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
			// cout << "vd[" << vdi << "] = " << entity->colour.x() << endl;
			vertexData[vdi++] = 1;
			// cout << "vd[" << vdi << "] = " << entity->colour.y() << endl;
			vertexData[vdi++] = 0.4;
			// cout << "vd[" << vdi << "] = " << entity->colour.z() << endl;
			vertexData[vdi++] = 0.4;

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
			StrUtils::split_string(line, edges, 2, ' ');

			// Loop through each split to extract the element data
			for (int i = 0; i < 3; i++) {

				string faceData[3];
				StrUtils::split_string(edges[i], faceData, 0, '/');
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

	// Need to create new VBO and EBO
	glGenVertexArrays(1, &this->buffers[this->numMeshes].vao);
	glGenBuffers(1, &this->buffers[this->numMeshes].vbo);
	glGenBuffers(1, &this->buffers[this->numMeshes].ebo);

	// Save buffer data
	mbd->vao	 = this->buffers[this->numMeshes].vao;
	mbd->vbo	 = this->buffers[this->numMeshes].vbo;
	mbd->ebo	 = this->buffers[this->numMeshes].ebo;
	mbd->eboSize = eboSize;

	// Compute the volume
	// entity->volume = Algorithms::compute_volume(vertices, vertexConnectionList, numFaces);
	// entity->boundingBox.set(minX, minY, minZ, maxX, maxY, maxZ);

	// Bind the current vertex array object
	glBindVertexArray(this->buffers[this->numMeshes].vao);

	// Bind the vbo for this mesh to make them active
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[this->numMeshes].vbo);

	// Store vertex data into the current active vertex buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	// Bind the element buffer for this object to make it active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers[this->numMeshes].ebo);

	// Store element data into the current active element buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elementData), elementData, GL_STATIC_DRAW);

	// Increment vbo Index
	this->numMeshes++;

	// /**
	//  * @brief The VBO holds the vertex data, the ebo holds the data that tells OpenGL how to connect
	//  * the vertices in the VBO when drawing. To decrease the amount of buffer binding during the
	//  * rendering process, we can bind a VAO to a VBO and EBO such that when the VAO is bound, the
	//  * VBO and EBO associated with that VAO are automatically bound. To do this, the VAO must know
	//  * the settings on how to use the VAO and EBO to draw the mesh correctly. The VAO, VBO and EBO
	//  * that are to be connected together must all be bound before the following code is executed.
	//  *
	//  * The following code will tell the VAO where the position and colour attributes in the vertex
	//  * shader and how to read the VBO data so that when the VAO is bound, OpenGP can automatically
	//  * get the correct vertex and colour data for each mesh.
	//  *
	//  * Note that correct shader id for this mesh must also be bound as well
	//  */

	// Ensure the correct shader is bound
	glUseProgram(baseShader->programId);

	// Get the location of the position variable
	GLuint vertexLocation = glGetAttribLocation(baseShader->programId, "position");

	/** Specify to OpenGL how the data in the vbo of any object using this vertex shader will be and used to
	 * supply the 'position' variable with data. Arguments:
	 * 		1: The GLuint location of the position variable in the shader
	 * 		2: Number of data points used to make up a single vertex (3 in this case i.e x, y, z)
	 * 		3: The type of data (float in this case)
	 * 		4: Whether the data is normalised. Don't actually know what this does, it was false in a tutorial
	 * 		5: Stride length i.e How many data points each vertex in a mesh has that is loaded into a vbo. In
	 * 			this case it is 6 as the meshes currently contain 3 vertex points and 3 colour values
	 * 		6: The pointer to the first index to start reading from. As the vertex data is within the first
	 * 			3 data values of information for each vertex, we keep this as 0 and OpenGL will read the first
	 * 			3 data values and use that as the vertex (because we set number of data points to be 3 in arg
	 * 			2)
	 */
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	// Inputs to a vertex shader are called vertex attributes. To enable a vertex attribute like
	// the vec3 input 'position', we must enable it by calling the following (This can be done
	// anywhere as long as it is done before rendering)
	glEnableVertexAttribArray(vertexLocation);

	// Get the location of the colour variable
	GLuint colourLocation = glGetAttribLocation(baseShader->programId, "colour");

	/** Specify to OpenGL how the data in the vbo of any object using this vertex shader will be and used to
	 * supply the 'colour' variable with data. Arguments:
	 * 		1: The GLuint location of the colour variable in the shader
	 * 		2: Number of data points used to make up a single colour (3 in this case i.e r, g, b)
	 * 		3: The type of data (float in this case)
	 * 		4: Whether the data is normalised. Don't actually know what this does, it was false in a tutorial
	 * 		5: Stride length i.e How many data points each vertex in a mesh has that is loaded into a vbo. In
	 * 			this case it is 6 as the meshes currently contain 3 vertex points and 3 colour values
	 * 		6: The pointer to the first index to start reading from. As the colour data is within the last 3
	 * 			data values of information for each vertex, we keep set this as 3 and OpenGL will skip the
	 * 			first 3 data points (vertex points) and use the next 3 data points (colour values)
	 */
	glVertexAttribPointer(colourLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Inputs to a vertex shader are called vertex attributes. To enable a vertex attribute like
	// the vec3 input 'colour', we must enable it by calling the following (This can be done
	// anywhere as long as it is done before rendering)
	glEnableVertexAttribArray(colourLocation);
}
