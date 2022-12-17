/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for vector3f
 * @version 0.1
 * @date Sun Nov 27 13:44:25 2022

 *
 * @copyright Copyright (c)
 *
 */

/* Public Includes */
#include <iostream>

/* GLEW Includes */

/* Private Includes */
#include "vector3f.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace vector3f;
using namespace std;

Vector3f::Vector3f() {
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
}

Vector3f::~Vector3f() {}

Vector3f::Vector3f(float xi, float yi, float zi) {
	v[0] = xi;
	v[1] = yi;
	v[2] = zi;
}

void Vector3f::add(float xi, float yi, float zi) {
	v[0] += xi;
	v[1] += yi;
	v[2] += zi;
}

void Vector3f::add(Vector3f vector) {
	v[0] += vector.v[0];
	v[1] += vector.v[1];
	v[2] += vector.v[2];
}

void Vector3f::set(float xi, float yi, float zi) {
	v[0] = xi;
	v[1] = yi;
	v[2] = zi;
}

void Vector3f::set(Vector3f vector) {
	v[0] = vector.v[0];
	v[1] = vector.v[1];
	v[2] = vector.v[2];
}

void Vector3f::print() {
	cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << endl;
}