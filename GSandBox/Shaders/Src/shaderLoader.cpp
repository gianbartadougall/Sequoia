/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for shaderLoader
 * @version 0.1
 * @date Sat Nov 26 22:34:49 2022

 *
 * @copyright Copyright (c)
 *
 */

/* Public Includes */
#include <iostream>
#include <fstream>

/* GLEW Includes */

/* Private Includes */
#include "shaderLoader.h"

/* Private Macros */
#define SHADER_LOADER_ERROR	 ((GLuint)-1)
#define SHADER_LOADER_SUCESS 0

/* Private Enumerations and Structures */

using namespace shaderLoader;
using namespace std;
using namespace debugLog;
using namespace vector3f;
using namespace vector4f;

ShaderLoader::ShaderLoader() {}

ShaderLoader::~ShaderLoader() {

	// Free memory of all the shader strings
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	free(compiledShader);
}

GLuint ShaderLoader::load_shader(string vertexShaderPath, string fragmentShaderPath) {

	// Compile the vertex shader
	GLuint vertexShaderId = compile_shader(vertexShaderPath, GL_VERTEX_SHADER);
	if (vertexShaderId == SHADER_LOADER_ERROR) {
		log.log_error("Vertex shader failed to compile");
		return SHADER_LOADER_ERROR;
	}

	// Compile the fragment shader
	GLuint fragmentShaderId = compile_shader(fragmentShaderPath, GL_FRAGMENT_SHADER);
	if (fragmentShaderId == SHADER_LOADER_ERROR) {
		log.log_error("Fragment shader failed to compile");
		return SHADER_LOADER_ERROR;
	}

	// Link the vertex and fragment shaders together
	GLuint shaderId = link_shaders(vertexShaderId, fragmentShaderId);
	if (shaderId == SHADER_LOADER_ERROR) {
		log.log_error("Vertex and fragment shader failed to link");
		return SHADER_LOADER_ERROR;
	}

	return shaderId;
}

GLuint ShaderLoader::compile_shader(string shaderFilePath, int shaderType) {

	// Generate shader
	GLuint shaderId		 = glCreateShader(shaderType);
	GLchar* shaderString = read_shader(shaderFilePath);

	// Bind the given shader file to the shader id and compile the shader
	glShaderSource(shaderId, 1, &shaderString, NULL);
	glCompileShader(shaderId);

	// Verify compilation was succesful
	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		return SHADER_LOADER_ERROR;
	}

	return shaderId;
}

GLchar* ShaderLoader::read_shader(std::string filePath) {

	// The file path is relative to the environment you call the executable from
	std::ifstream textFile(filePath);

	if (textFile.is_open() != true) {
		std::cout << "Unable to open '" << filePath << "'\n";
		return NULL;
	}

	// Get the length of the file
	char c;
	int length = 0;
	while ((textFile >> std::noskipws >> c) && (c != '\0')) {
		length++;
	}

	textFile.clear();  // Clear EOF flag
	textFile.seekg(0); // Return back to start of file

	// Copy string into char array
	compiledShader = new GLchar[length + 1];
	for (int i = 0; i < length; i++) {
		// noskipws ensures that white space is not skipped when reading file
		textFile >> std::noskipws >> compiledShader[i];
	}

	compiledShader[length] = '\0';

	// Close file
	textFile.close();

	return compiledShader;
}

GLuint ShaderLoader::link_shaders(GLuint vertexShaderId, GLuint fragmentShaderId) {

	shaderProgramId = glCreateProgram();
	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, fragmentShaderId);
	glBindFragDataLocation(shaderProgramId, 0, "outColour");

	// Linking the shader program required for connect to occur
	glLinkProgram(shaderProgramId);

	// // Confirm linking was succesful
	int success;
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		return SHADER_LOADER_ERROR;
	}

	glUseProgram(shaderProgramId);

	// posAttrib = glGetAttribLocation(shaderProgramId, "position");
	// std::cout << "Pos attrib: " << posAttrib << std::endl;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glBindAttribLocation(shaderProgramId, 0, "position");

	// To make OpenGL take in the colour data we need to do the following
	// colAttrib = glGetAttribLocation(shaderProgramId, "colour");
	// std::cout << "Col attrib: " << colAttrib << std::endl;
	// glEnableVertexAttribArray(colAttrib);
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Print out all these errors that occurred
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		cout << "Error occurred. Code : " << err << endl;
		// Process/log the error.
	}

	return shaderProgramId;
}

void ShaderLoader::load_vertex_shader_attributes(GLuint shaderProgramId, Vector3f translation, Vector3f scale,
												 Vector4f rotation) {

	glUseProgram(shaderProgramId);

	GLint floatTrans = glGetUniformLocation(shaderProgramId, "rotate");
	glUniform4fv(floatTrans, 1, rotation.v);

	GLint scaleTrans = glGetUniformLocation(shaderProgramId, "scale");
	glUniform3fv(scaleTrans, 1, scale.v);

	GLint translateTrans = glGetUniformLocation(shaderProgramId, "translation");
	glUniform3fv(translateTrans, 1, translation.v);
}

void ShaderLoader::load_fragment_shader_attributes() {}