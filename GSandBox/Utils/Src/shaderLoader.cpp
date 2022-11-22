/**
 * @file fileHandler.cpp
 * @author Gian Barta-Dougall
 * @brief System file for fileHandler
 * @version 0.1
 * @date --
 *
 * @copyright Copyright (c)
 *
 */
/* Public Includes */
#include <iostream>
#include <fstream>

/* Private Includes */
#include "shaderLoader.h"

/* GLEW Includes */
#include <GL/glew.h>

using namespace shaderLoader;

const int numShaders            = 2;
int shaderIndex                 = 0;
const char* shaders[numShaders] = {"vertex_shader.glsl", "fragment_shader.glsl"};
GLchar* compiledShaders[numShaders];

ShaderLoader::ShaderLoader() {

    // Compile all shaders
}

ShaderLoader::~ShaderLoader() {}

GLchar* ShaderLoader::load_shader(std::string filePath) {

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
    compiledShaders[shaderIndex] = new GLchar[length + 1];
    for (int i = 0; i < length; i++) {
        // noskipws ensures that white space is not skipped when reading file
        textFile >> std::noskipws >> compiledShaders[shaderIndex][i];
    }

    compiledShaders[shaderIndex][length] = '\0';

    // Close file
    textFile.close();

    shaderIndex++;
    return compiledShaders[shaderIndex - 1];
}