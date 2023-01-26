/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for shader
 * @version 0.1
 * @date Sat Nov 26 23:22:30 2022

 *
 * @copyright Copyright (c)
 *
 */
#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

/* Public Includes */

/* GLEW Includes */
#define GLEW_STATIC
#include <GL/glew.h>

/* Private Includes */
#include "vector4f.h"
#include "vector3f.h"
#include "debugLog.h"
#include "baseShader.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace vector3f;
using namespace vector4f;
using namespace baseShader;

namespace shaderLoader {

	class ShaderLoader {

		// Private variables
		GLchar* compiledShader;

		public:
		GLuint vertexShaderId;
		GLuint fragmentShaderId;
		GLuint shaderProgramId;
		GLuint posAttrib;
		GLuint colAttrib;

		ShaderLoader();
		~ShaderLoader();

		void load_baseshader(string line, BaseShader* shader);
		// GLuint load_shader(string vertexShader, string fragmentShader);
		// void load_fragment_shader_attributes();
		// void load_vertex_shader_attributes(GLuint shaderProgramId, Vector3f translation, Vector3f scale,
		// 								   Vector4f rotation);

		// GLchar* read_shader(std::string filePath);
		// GLuint link_shaders(GLuint vertexShaderId, GLuint fragmentShaderId);
		// GLuint compile_shader(string shaderFilePath, int shaderType);
		GLuint find_shader_variable_location(GLuint shaderId, string variableName);

		GLuint load_shader(string vertexShaderPath, string fragmentShaderPath);
		void load_fragment_shader_attributes();
		void load_vertex_shader_attributes(GLuint shaderProgramId, Vector3f translation, Vector3f scale,
										   Vector4f rotation);

		GLchar* read_shader(std::string filePath);
		GLuint link_shaders(GLuint vertexShaderId, GLuint fragmentShaderId);
		GLuint compile_shader(string shaderFilePath, int shaderType);

		private:
	};
} // namespace shaderLoader

#endif // SHADER_LOADER_H
