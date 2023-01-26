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

/* C Library Includes */

/* GLEW Includes */

/* Personal Includes */
#include "collision.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace collision;

Collision::Collision() {}

Collision::~Collision() {}

void Collision::rigid_body_collision(Object** entities, int numEntities) {

	for (int i = 0; i < numEntities; i++) {
		for (int j = 0; j < numEntities; j++) {

			Entity* e1 = entities[i];
			Entity* e2 = entities[j];

			// Skip collision detection if both entities are the same
			if (e1 == e2) {
				continue;
			}

			// Skip if there is no collision
			if (e1->boundingBox.collision(&e2->boundingBox) == false) {
				continue;
			}

			/* All collisions are perfectly elastic */

			// Precompute constants
			float mRatio  = e2->mass / e1->mass;
			float e1Ratio = (1 - mRatio) / (1 + mRatio);
			float e2Ratio = (mRatio - 1) / (1 + mRatio);

			// Save the values of the initial velocities of both objects
			float v1ix = e1->velocity.x();
			float v1iy = e1->velocity.y();
			float v1iz = e1->velocity.z();

			float v2ix = e2->velocity.x();
			float v2iy = e2->velocity.y();
			float v2iz = e2->velocity.z();

			// Calculate the resulting velocitiy of entity 1 after the collision
			e1->velocity.set_x(e1Ratio * (v1ix - v2ix));
			e1->velocity.set_y(e1Ratio * (v1iy - v2iy));
			e1->velocity.set_z(e1Ratio * (v1iz - v2iz));

			// Calculate the resulting velocitiy of entity 2 after the collision
			e2->velocity.set_x(e2Ratio * (v2ix - v1ix));
			e2->velocity.set_y(e2Ratio * (v2iy - v1iy));
			e2->velocity.set_z(e2Ratio * (v2iz - v1iz));
		}
	}
}

void rigid_body_vertical_collision(Entity* e1, Entity* e2) {}
