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

/* C Library Includes */
#include <iostream>

/* GLEW Includes */

/* Personal Includes */
#include "entity.h"

/* Private Macros */
#define POS_X	1
#define POS_Y	2
#define POS_Z	3
#define ROT_X	4
#define ROT_Y	5
#define ROT_Z	6
#define SCL_X	7
#define SCL_Y	8
#define SCL_Z	9
#define COL_R	10
#define COL_G	11
#define COL_B	12
#define DENSITY 13

/* Private Enumerations and Structures */

using namespace entity;
using namespace std;

Entity::Entity() {

	acceleration.set(0, 0, 0);
	velocity.set(0, 0, 0);
	position.set(0, 0, 0);
}

Entity::~Entity() {}

void Entity::load_shader(BaseShader* shader) {
	this->shader = shader;
}

void Entity::print() {}

void Entity::update() {

	// Reset timer if the acceleration is 0. This ensures as soon as the acceleration is not 0,
	// the amount of time the acceleration exists for is known
	if (this->acceleration.y() == 0) {
		// Set the acceleration to current time
		this->accelerationTimeMs = time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count();
	}

	// Apply gravity
	if (this->position.y() > 0) {
		this->acceleration.set_y(phys->GRAVITY);
	}

	if (this->position.y() > 0) {
		// If the objects height is above 0, set the acceleration to earth's acceleration. For now
		// gravity is set to -0.01. -9.81 would be far too quick
		this->acceleration.set_y(phys->GRAVITY);
	}

	// Calculate time step. Note that the time step is in milliseconds so make sure that the number of
	// milliseconds that have passed < ~ 4 billion otherwise the integer will overflow and you will get
	// some weird results
	uint32_t timeStepMs =
		time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count() - this->accelerationTimeMs;
	float timeStep = timeStepMs / 1000.0;
	// cout << timeStepMs << " " << timeStep << "\n";

	// Calculate the velocity of the object from its acceleration
	this->velocity.add_x(this->acceleration.x() * timeStep);
	this->velocity.add_y(this->acceleration.y() * timeStep);
	this->velocity.add_z(this->acceleration.z() * timeStep);

	// Calculate the postion of the object from its velocity
	this->position.add_y(this->velocity.y() * timeStep);
	this->position.add_x(this->velocity.x() * timeStep);
	this->position.add_z(this->velocity.z() * timeStep);

	// // Default behaviour of an entity is to fall due to gravity
	if (this->position.y() <= 0) {
		this->position.set_y(0);
		this->acceleration.v[1] = 0;
	}
}

Vector3f Entity::get_position() {
	return this->position;
}

void Entity::set_shader(BaseShader* shader) {
	this->shader = shader;
}

void Entity::init(MeshBufferData* mbd, string objectData) {

	this->vao = mbd->vao;
	cout << "Set VAO to: " << this->vao << endl;
	this->eboSize = mbd->eboSize;

	// Objects are stored in following format
	// E,shaderId,xPos,yPos,zPos,xRot,yRot,zRot,xScl,yScl,zScl,r,g,b,density
	string data[14];
	StrUtils::split_string(objectData, data, 0, ',');

	// Load the colour early so the data can be stored into the vbo
	this->colour.set(stof(data[COL_R]), stof(data[COL_G]), stof(data[COL_B]));

	// Set the initial position of this object
	this->position.set(stof(data[POS_X]), stof(data[POS_Y]), stof(data[POS_Z]));
	this->rotation.set(stof(data[ROT_X]), stof(data[ROT_Y]), stof(data[ROT_Z]));
	this->scale.set(stof(data[SCL_X]), stof(data[SCL_Y]), stof(data[SCL_Z]));

	this->density = stof(data[DENSITY]);

	// Calcualte the mass of the object.
	// Need to recalc volume as it isn't calced //
	this->mass = 10;
}