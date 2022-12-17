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

/* GLEW Includes */

/* Private Includes */
#include "entity.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace entity;

Entity::Entity() {

	// Generate buffers for vbo and the ebo
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
}

Entity::~Entity() {

	// Delete all dynamic objects
	glDeleteBuffers(1, &this->vbo);
	glDeleteBuffers(1, &this->ebo);
}

void Entity::load_shader(BaseShader* shader) {
	this->shader = shader;
}