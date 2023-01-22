/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for baseShader
 * @version 0.1
 * @date Sat Dec 17 13:36:38 2022

 *
 * @copyright Copyright (c)
 *
 */
#ifndef BASE_SHADER_H
#define BASE_SHADER_H

/* Public Includes */

/* GLEW Includes */
#include "GL/glew.h"

/* Private Includes */

/* Public Macros */

/* Public Enumerations and Structures */

namespace baseShader {

	class BaseShader {

		// Private variables

		public:
		BaseShader();
		~BaseShader();

		// Shader id
		GLuint programId;

		/* Location ids for attributes within the vertex shaders */
		GLuint vertexLocation;
		GLuint transformationMatrixLocation;
		GLuint projectionMatrixLocation;
		GLuint viewMatrixLocation;
		GLuint cameraRotationLocation;
		GLuint cameraPositionLocation;

		void print();
	};
} // namespace baseShader

#endif // BASE_SHADER_H
