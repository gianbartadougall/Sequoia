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
#ifndef OBJECT_H
#define OBJECT_H

/* Public Includes */

/* GLEW Includes */

/* Private Includes */
#include "mesh.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace mesh;

namespace object {

	class Object {

		// Private variables

		public:
		Mesh* mesh;

		Object();
		~Object();
	};
} // namespace object

#endif // OBJECT_H
