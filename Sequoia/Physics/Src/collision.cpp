/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for collision
 * @version 0.1
 * @date Tue Jan 24 20:31:43 2023

 *
 * @copyright Copyright (c)
 *
 */

/* Public Includes */

/* GLEW Includes */

/* Private Includes */
#include "collision.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace collision;

Collision::Collision() {}

Collision::~Collision() {}

void Collision::rigid_body_collision(Entity* e1, Entity* e2) {

	// // Check whether the bounding boxes have hit eachother or not
	// if (e1->boundingBox.collision(e2->boundingBox) != true) {
	// 	return;
	// }

	// Apply
}
