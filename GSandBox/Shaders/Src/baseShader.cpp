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

/* Public Includes */
#include <iostream>

/* GLEW Includes */

/* Private Includes */
#include "baseShader.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace baseShader;
using namespace std;

BaseShader::BaseShader() {}

BaseShader::~BaseShader() {}

void BaseShader::print() {
	cout << "Program Id: " << this->programId << endl;
	cout << "View Matrix id: " << this->viewMatrixLocation << endl;
	cout << "Projection Matrix id: " << this->projectionMatrixLocation << endl;
	cout << "Transformation Matrix id: " << this->transformationMatrixLocation << endl;
}