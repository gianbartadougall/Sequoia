/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for boundingBox
 * @version 0.1
 * @date Sun Jan 22 23:16:21 2023

 *
 * @copyright Copyright (c)
 *
 */

/* C Library Includes */
#include <iostream>

/* GLEW Includes */

/* Private Includes */
#include "boundingBox.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace std;

using namespace boundingBox;

BoundingBox::BoundingBox() {}

BoundingBox::BoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	this->minX = minX;
	this->minY = minY;
	this->minZ = minZ;
	this->maxX = maxX;
	this->maxY = maxY;
	this->maxZ = maxZ;
}

BoundingBox::~BoundingBox() {}

void BoundingBox::set(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
	this->minX = minX;
	this->minY = minY;
	this->minZ = minZ;
	this->maxX = maxX;
	this->maxY = maxY;
	this->maxZ = maxZ;
}

float BoundingBox::volume() {

	float length = this->length();

	return length * length * length;
}

float BoundingBox::length() {

	float x = maxX - minX;
	float y = maxY - minY;
	float z = maxZ - minZ;

	// Return the volume of a cube that covers the largest side length
	if (x > y && x > z) {
		return x;
	}

	if (y > x && y > z) {
		return y;
	}

	if (z > x && z > y) {
		return z;
	}

	// All sides have the same length
	return x;
}

int BoundingBox::collision(BoundingBox* box) {

	if (this->minX > box->maxX) {
		return false;
	}

	if (this->minY > box->maxY) {
		return false;
	}

	if (this->minZ > box->maxZ) {
		return false;
	}

	if (this->maxX < box->minX) {
		return false;
	}

	if (this->maxY < box->minY) {
		return false;
	}

	if (this->maxZ < box->minZ) {
		return false;
	}

	return true;
}