/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for renderer
 * @version 0.1
 * @date Sat Dec 17 11:23:10 2022

 *
 * @copyright Copyright (c)
 *
 */
#ifndef RENDERER_H
#define RENDERER_H

/* Public Includes */

/* GLEW Includes */
#define GLEW_STATIC
#include "GL/glew.h"

/* Private Includes */
#include "matrix4f.h"
#include "object.h"
#include "camera.h"
#include "entity.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace matrix4f;
using namespace object;
using namespace camera;
using namespace entity;

namespace renderer {

	class Renderer {

		/* Private Variables */
		Matrix4f projectionMatrix;
		GLuint currentShaderId;

		/* Private Functions for rendering Objects */
		void load_object_shader_values(Object* object);
		void render_objects(GLuint* vaos, int numVaos, Object* objects, int* objectListSizes, Camera* camera);

		void load_generic_shader_values(Entity* entity);

		public:
		Renderer();
		~Renderer();

		void render(GLuint* vaos, int numVaos, Camera* camera, Object* objects, int* objectListSizes);
	};

} // namespace renderer

#endif // RENDERER_H
