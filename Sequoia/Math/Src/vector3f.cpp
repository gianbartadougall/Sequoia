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

void Vector3f::add_x(float xi) {
	v[0] += xi;
}

void Vector3f::add_y(float yi) {
	v[1] += yi;
}

void Vector3f::add_z(float zi) {
	v[2] += zi;
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

void Vector3f::set_x(float xi) {
	v[0] = xi;
}

void Vector3f::set_y(float yi) {
	v[1] = yi;
}

void Vector3f::set_z(float zi) {
	v[2] = zi;
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

void Vector3f::cross(Vector3f v) {
	this->v[0] = ((v.z() * this->y()) - (v.y() * this->z()));
	this->v[1] = ((v.x() * this->z()) - (v.z() * this->x()));
	this->v[2] = ((v.y() * this->x()) - (v.x() * this->y()));
}

float Vector3f::x() {
	return this->v[0];
}

float Vector3f::y() {
	return this->v[1];
}

float Vector3f::z() {
	return this->v[2];
}

void Vector3f::print() {
	cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")" << endl;
}

static Vector3f cross(Vector3f v1, Vector3f v2) {
	v1.v[0] = ((v2.z() * v1.y()) - (v2.y() * v1.z()));
	v1.v[1] = ((v2.x() * v1.z()) - (v2.z() * v1.x()));
	v1.v[2] = ((v2.y() * v1.x()) - (v2.x() * v1.y()));
}