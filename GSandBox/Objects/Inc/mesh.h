/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief This class holds the mesh data of an object.
 * @version 0.1
 * @date Sun Nov 27 20:34:58 2022
 *
 *
 * @copyright Copyright (c)
 *
 */
#ifndef MESH_H
#define MESH_H

/* Public Includes */
#include <string>

/* GLEW Includes */
#define GLEW_STATIC
#include <GL/glew.h>

/* Private Includes */
#include "debugLog.h"
#include "vector3f.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace std;
using namespace debugLog;
using namespace vector3f;

namespace mesh {

	class Mesh {

		// Private variables
		debugLog::DebugLog log;

		public:
		GLuint vbo; // Vertex buffer object

		GLuint ebo; // Element buffer object
		int eboSize;

		Mesh(GLuint vboId, GLuint eboId);
		~Mesh();

		void load_mesh(string objectFilePath, Vector3f colour);

		private:
		void split_triplet(string line, string* splitList, int start, char delimiter);
	};
} // namespace mesh

#endif // MESH_H
