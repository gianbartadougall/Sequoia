/**
 * @file objectLoader.h
 * @author Gian Barta-Dougall
 * @brief System file for objectLoader
 * @version 0.1
 * @date --
 *
 * @copyright Copyright (c)
 *
 */
#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

/* C Library Includes */
#include <string.h>

/* GLEW Includes */
#define GLEW_STATIC
#include <GL/glew.h>

/* Personal Includes */
#include "debugLog.h"
#include "baseShader.h"

/* Public Macros */
#define MAX_MESH_TYPES 3
#define MAX_MESHES	   5

/* Public Enumerations and Structures */

typedef struct MeshBufferData {
	GLuint vao;
	GLuint vbo;
	GLuint ebo;
	int eboSize;
} MeshBufferData;

using namespace debugLog;
using namespace baseShader;

namespace objectLoader {

	class ObjectLoader {

		// Private variables

		// Variable to store how many objects have been loaded
		int objectIndex = 0;

		struct MeshBufferData buffers[MAX_MESHES];

		int numMeshes = 0;

		public:
		ObjectLoader();
		~ObjectLoader();

		GLuint new_vao();
		void new_object(string filePath, BaseShader* baseShader, MeshBufferData* mbd);
	};
} // namespace objectLoader

#endif // OBJECTLOADER_H