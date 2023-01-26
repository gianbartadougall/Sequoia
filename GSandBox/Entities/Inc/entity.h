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
#include <chrono>

/* GLEW Includes */
#define GLEW_STATIC
#include "GL/glew.h"

/* Private Includes */
#include "mesh.h"
#include "vector3f.h"
#include "vector3i.h"
#include "debugLog.h"
#include "baseShader.h"
#include "boundingBox.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace vector3f;
using namespace vector3i;
using namespace baseShader;
using namespace std::chrono;
using namespace boundingBox;

namespace entity {

	class Entity {

		// Private variables
		debugLog::DebugLog log;

		protected:
		Vector3f position;

		long long accelerationTimeMs;
		Vector3f acceleration;

		public:
		// Ids for the mesh of the entity to stored for rendering
		GLuint vbo;
		GLuint ebo;
		int eboSize;

		// ID for the entity to be rendered using the correct shader program
		BaseShader* shader;

		// Mesh Attributes. These will eventually need to be put in their own class at some point
		BoundingBox boundingBox;
		float volume;

		// Attributes to place the entity in the correct location/orientation/scale in the world
		Vector3f rotation;
		Vector3f scale;

		Entity();
		~Entity();

		void print();
		void load_shader(BaseShader* shader);
		void update();

		Vector3f get_position();
	};
} // namespace entity

#endif // ENTITY_H
