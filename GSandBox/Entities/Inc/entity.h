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

/* C Library Includes */
#include <string>
#include <chrono>

/* GLEW Includes */
#define GLEW_STATIC
#include "GL/glew.h"

/* Personal Includes */
#include "vector3f.h"
#include "vector3i.h"
#include "debugLog.h"
#include "baseShader.h"
#include "boundingBox.h"
#include "physicsSettings.h"
#include "objectLoader.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace vector3f;
using namespace vector3i;
using namespace baseShader;
using namespace std::chrono;
using namespace boundingBox;
using namespace physicsSettings;

namespace entity {

	class Entity {

		// Private variables

		protected:
		PhysicsSettings* phys;

		long long accelerationTimeMs;

		public:
		// Ids for the mesh of the entity to stored for rendering
		GLuint vao; // Pointer to the vao that renders this entity
		int eboSize;
		// GLuint vbo;
		// GLuint ebo;

		// ID for the entity to be rendered using the correct shader program
		BaseShader* shader;

		// Mesh Attributes. These will eventually need to be put in their own class at some point
		BoundingBox boundingBox;
		Vector3f position;
		Vector3f velocity;
		Vector3f acceleration;
		float volume;
		float mass;
		float density;

		// Attributes to place the entity in the correct location/orientation/scale in the world
		Vector3f rotation;
		Vector3f scale;
		Vector3f colour;

		Entity();
		~Entity();

		void init(MeshBufferData* mbd, string line);
		void set_shader(BaseShader* shaderId);
		void print();
		void load_shader(BaseShader* shader);
		void update();
		void load_physics_settings(PhysicsSettings* physSettings) {
			phys = physSettings;
		}

		Vector3f get_position();
	};
} // namespace entity

#endif // ENTITY_H
