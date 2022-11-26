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

/* Private Includes */
#include "debugLog.h"

/* Public Macros */
#define MAX_NUM_OBJECTS 1

using namespace debugLog;

namespace objectLoader {

	class ObjectLoader {

		// Private variables
		debugLog::DebugLog debugLog;

		// Variable to store how many objects have been loaded
		int objectIndex = 0;

		// Create array of vertex buffers
		GLuint vba[MAX_NUM_OBJECTS];

		// Create array of element buffers
		GLuint eba[MAX_NUM_OBJECTS];

		GLuint vao;

		public:
		ObjectLoader();
		~ObjectLoader();

		void load_3D_object(string path);
		void split_triplet(string data, string* splitList, int start, char delimiter);
	};
} // namespace objectLoader

#endif // OBJECTLOADER_H
