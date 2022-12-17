/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for entity
 * @version 0.1
 * @date Sun Dec 11 12:25:33 2022

 *
 * @copyright Copyright (c)
 *
 */
#ifndef ENTITY_H
#define ENTITY_H

/* Public Includes */
#include <string>

/* GLEW Includes */
#define GLEW_STATIC
#include "GL/glew.h"

/* Private Includes */
#include "mesh.h"
#include "vector3f.h"
#include "debugLog.h"
#include "baseShader.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace vector3f;
using namespace baseShader;

namespace entity {

	class Entity {

		// Private variables
		debugLog::DebugLog log;

		public:
		// Ids for the mesh of the entity to stored for rendering
		GLuint vbo;
		GLuint ebo;
		int eboSize;

		// ID for the entity to be rendered using the correct shader program
		BaseShader* shader;

		// Attributes to place the entity in the correct location/orientation/scale in the world
		Vector3f position;
		Vector3f rotation;
		Vector3f scale;

		Entity();
		~Entity();

		void print();
		void load_shader(BaseShader* shader);
	};
} // namespace entity

#endif // ENTITY_H
