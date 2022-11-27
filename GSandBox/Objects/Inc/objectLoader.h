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

/* Public Includes */
#include <string.h>

/* GLEW Includes */
#define GLEW_STATIC
#include <GL/glew.h>

/* Private Includes */
#include "debugLog.h"
#include "object.h"

/* Public Macros */
#define MAX_NUM_OBJECTS 1

/* Public Enumerations and Structures */
typedef struct ObjectData {
	GLuint elementBuffer;
	int elementArraySize;
} ObjectData;

using namespace debugLog;
using namespace object;

namespace objectLoader {

	class ObjectLoader {

		// Private variables
		debugLog::DebugLog log;

		// Variable to store how many objects have been loaded
		int objectIndex = 0;

		// Array for vertex buffers and element buffers
		GLuint* vba;
		GLuint* eba;

		GLuint vao;

		object::Object* objects;
		int numObjects;

		public:
		ObjectLoader();
		~ObjectLoader();
		Object* load_objects(string objectFileNames[], int numObjects);
		void load_3D_object(string path, ObjectData* objects);
		void split_triplet(string data, string* splitList, int start, char delimiter);
	};
} // namespace objectLoader

#endif // OBJECTLOADER_H