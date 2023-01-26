/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for int3f
 * @version 0.1
 * @date Sat Jan 07 20:48:53 2023

 *
 * @copyright Copyright (c)
 *
 */

/* Public Includes */

/* GLEW Includes */

/* Private Includes */
#include "vector3i.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace vector3i;

Vector3i::Vector3i() {}

Vector3i::~Vector3i() {}

void Vector3i::set_x(int x) {
	this->v[0] = x;
}

void Vector3i::set_y(int y) {
	this->v[1] = y;
}

void Vector3i::set_z(int z) {
	this->v[2] = z;
}

void Vector3i::set(int x, int y, int z) {
	this->v[0] = x;
	this->v[1] = y;
	this->v[2] = z;
}
