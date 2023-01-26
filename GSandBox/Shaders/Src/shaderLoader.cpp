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
#include "strUtils.h"
#include "gameSettings.h"
#include "matrix4f.h"

/* Private Macros */
#define SHADER_LOADER_ERROR	 ((GLuint)-1)
#define SHADER_LOADER_SUCESS 0

/* Private Enumerations and Structures */

using namespace shaderLoader;
using namespace std;
using namespace debugLog;
using namespace vector3f;
using namespace vector4f;
using namespace strUtils;
using namespace matrix4f;

ShaderLoader::ShaderLoader() {}

ShaderLoader::~ShaderLoader() {}

void ShaderLoader::load_baseshader(string line, BaseShader* shader) {

	// Extract the file paths to the vertex and fragment shaders
	string shaders[2];
	StrUtils utils;
	utils.split_string(line, shaders, 2, ',');

	// Compile the vertex and fragment shader and then link the shaders together
	shader->vertexShaderId	 = compile_shader(shaders[0], GL_VERTEX_SHADER);
	shader->fragmentShaderId = compile_shader(shaders[1], GL_FRAGMENT_SHADER);
	shader->programId		 = link_shaders(shader->vertexShaderId, shader->fragmentShaderId);

	glUseProgram(shader->programId);

	// // Get the location of the position variable
	// GLuint vertexLocation = glGetAttribLocation(shader->programId, "position");

	// /** Specify to OpenGL how the data in the vbo of any object using this vertex shader will be and used to
	//  * supply the 'position' variable with data. Arguments:
	//  * 		1: The GLuint location of the position variable in the shader
	//  * 		2: Number of data points used to make up a single vertex (3 in this case i.e x, y, z)
	//  * 		3: The type of data (float in this case)
	//  * 		4: Whether the data is normalised. Don't actually know what this does, it was false in a tutorial
	//  * 		5: Stride length i.e How many data points each vertex in a mesh has that is loaded into a vbo. In
	//  * 			this case it is 6 as the meshes currently contain 3 vertex points and 3 colour values
	//  * 		6: The pointer to the first index to start reading from. As the vertex data is within the first
	//  * 			3 data values of information for each vertex, we keep this as 0 and OpenGL will read the first
	//  * 			3 data values and use that as the vertex (because we set number of data points to be 3 in arg
	//  * 			2)
	//  */
	// glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	// // Inputs to a vertex shader are called vertex attributes. To enable a vertex attribute like
	// // the vec3 input 'position', we must enable it by calling the following (This can be done
	// // anywhere as long as it is done before rendering)
	// glEnableVertexAttribArray(vertexLocation);

	// // Get the location of the colour variable
	// GLuint colourLocation = glGetAttribLocation(shader->programId, "colour");

	// /** Specify to OpenGL how the data in the vbo of any object using this vertex shader will be and used to
	//  * supply the 'colour' variable with data. Arguments:
	//  * 		1: The GLuint location of the colour variable in the shader
	//  * 		2: Number of data points used to make up a single colour (3 in this case i.e r, g, b)
	//  * 		3: The type of data (float in this case)
	//  * 		4: Whether the data is normalised. Don't actually know what this does, it was false in a tutorial
	//  * 		5: Stride length i.e How many data points each vertex in a mesh has that is loaded into a vbo. In
	//  * 			this case it is 6 as the meshes currently contain 3 vertex points and 3 colour values
	//  * 		6: The pointer to the first index to start reading from. As the colour data is within the last 3
	//  * 			data values of information for each vertex, we keep set this as 3 and OpenGL will skip the
	//  * 			first 3 data points (vertex points) and use the next 3 data points (colour values)
	//  */
	// glVertexAttribPointer(colourLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// // Inputs to a vertex shader are called vertex attributes. To enable a vertex attribute like
	// // the vec3 input 'colour', we must enable it by calling the following (This can be done
	// // anywhere as long as it is done before rendering)
	// glEnableVertexAttribArray(colourLocation);

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		DebugLog::log_error("Shader Error occured 2");
		cout << "Code: " << err << endl;
		// Process/log the error.
	}

	// Get the location of generic uniforms
	shader->transformationMatrixLocation = find_shader_variable_location(shader->programId, "transformationMatrix");
	shader->projectionMatrixLocation	 = find_shader_variable_location(shader->programId, "projectionMatrix");
	shader->cameraRotationLocation		 = find_shader_variable_location(shader->programId, "cameraRotation");
	shader->cameraPositionLocation		 = find_shader_variable_location(shader->programId, "cameraPosition");

	// Load the projection matrix immediatley into each shader
	Matrix4f projectionMatrix;
	projectionMatrix.projection_matrix(WINDOW_WIDTH, WINDOW_HEIGHT, 0.1, 1000);
	glUniformMatrix4fv(shader->projectionMatrixLocation, 1, GL_FALSE, projectionMatrix.m);

	// Print out all these errors that occurred
	// GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		DebugLog::log_error("Shader Error occured");
		cout << "Code: " << err << endl;
		// Process/log the error.
	}
}

GLuint ShaderLoader::compile_shader(string shaderFilePath, int shaderType) {

	// Generate shader
	GLuint shaderId		 = glCreateShader(shaderType);
	GLchar* shaderString = read_shader(shaderFilePath);

	// Bind the given shader file to the shader id and compile the shader
	glShaderSource(shaderId, 1, &shaderString, NULL);
	glCompileShader(shaderId);

	delete shaderString;

	// Verify compilation was succesful
	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE) {
		DebugLog::log_error("Could not compile shader");
		cout << shaderFilePath << endl;
	}

	return shaderId;
}

GLchar* ShaderLoader::read_shader(string filePath) {

	// The file path is relative to the environment you call the executable from
	std::ifstream textFile(filePath);

	if (textFile.is_open() != true) {
		std::cout << "Unable to open '" << filePath << "'\n";
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
	GLchar* shaderStr = new GLchar[length + 1];
	for (int i = 0; i < length; i++) {
		// noskipws ensures that white space is not skipped when reading file
		textFile >> std::noskipws >> shaderStr[i];
	}

	shaderStr[length] = '\0';

	// Close file
	textFile.close();

	return shaderStr;
}

GLuint ShaderLoader::link_shaders(GLuint vertexShaderId, GLuint fragmentShaderId) {

	GLuint shaderProgramId = glCreateProgram();
	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, fragmentShaderId);
	glBindFragDataLocation(shaderProgramId, 0, "outColour");

	// Linking the shader program required for connect to occur
	glLinkProgram(shaderProgramId);

	// Confirm linking was succesful
	int success;
	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	if (success != GL_TRUE) {
		DebugLog::log_error("Shader failed to link");
	}

	return shaderProgramId;
}

GLuint ShaderLoader::find_shader_variable_location(GLuint shaderId, string variableName) {

	GLint locationId = glGetUniformLocation(shaderId, (GLchar*)variableName.c_str());

	if (locationId < 0) {
		DebugLog::log_error("Failed to load shader attribute");
		cout << variableName << " has error: " << locationId << endl;
	}

	return locationId;
}