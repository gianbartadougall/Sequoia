/**
 * @file shaderLoader.h
 * @author Gian Barta-Dougall
 * @brief System file for shaderLoader
 * @version 0.1
 * @date --
 *
 * @copyright Copyright (c)
 *
 */
#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

/* Public Includes */
#include <string>

/* GLEW Includes */
#include <GL/glew.h>

namespace shaderLoader {

	class ShaderLoader {

		// Private variables

		public:
		ShaderLoader();
		~ShaderLoader();

		GLchar* load_shader(std::string filePath);
	};

} // namespace shaderLoader

#endif // SHADER_LOADER_H
