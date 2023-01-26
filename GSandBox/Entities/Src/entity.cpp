/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for entity
 * @version 0.1
 * @date Sun Dec 11 12:25:33 2022

 *
 * @copyright Copyright (c)
 *
 */

/* Public Includes */
#include <iostream>

/* GLEW Includes */

/* Private Includes */
#include "entity.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace entity;
using namespace std;

Entity::Entity() {

	// Generate buffers for vbo and the ebo
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);

	acceleration.set(0, 0, 0);
	position.set(0, 0, 0);
}

Entity::~Entity() {

	// Delete all dynamic objects
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ebo);
}

void Entity::load_shader(BaseShader* shader) {
	this->shader = shader;
}

void Entity::print() {
	cout << "Vbo: " << vbo << endl;
	cout << "Ebo: " << ebo << endl;
	cout << "Ebo size: " << eboSize << endl;
}

void Entity::update() {

	// Check if the object is currently at ground
	if (this->position.y() == 0) {
		return;
	}

	// Reset timer if the acceleration is 0. This ensures as soon as the acceleration is not 0,
	// the amount of time the acceleration exists for is known
	if (this->acceleration.y() == 0) {
		// Set the acceleration to current time
		this->accelerationTimeMs = time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count();
	}

	// Increase acceleration up to maximum value
	if (this->acceleration.v[1] > -0.005) {
		this->acceleration.add_y(-0.00001);
	}

	// Calculate time step. Note that the time step is in milliseconds so make sure that the number of
	// milliseconds that have passed < ~ 4 billion otherwise the integer will overflow and you will get
	// some weird results
	uint32_t timeStepMs =
		time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count() - this->accelerationTimeMs;

	// Calculate how much the object will fall due to gravity
	float nextYPosition = ((acceleration.y() * (float)(timeStepMs * timeStepMs)) / 1000000) + position.v[1];

	/****** START CODE BLOCK ******/
	// Description: Determine whether the next position is valid or not

	/****** END CODE BLOCK ******/

	position.v[1] = nextYPosition;

	// Default behaviour of an entity is to fall due to gravity
	if (this->position.y() <= 0) {
		this->position.set_y(0);
		this->acceleration.v[1] = 0;
	}
}

Vector3f Entity::get_position() {
	return this->position;
}