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
#ifndef COLLISION_H
#define COLLISION_H

/* C Library Includes */

/* GLEW Includes */

/* Personal Includes */
#include "entity.h"
#include "object.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace entity;
using namespace object;

namespace collision {

	class Collision {

		// Private variables

		public:
		Collision();
		~Collision();

		static void rigid_body_collision(Object** entites, int numEntities);

		static bool rigid_body_vertical_collision(Entity* e1, Entity* e2);
	};
} // namespace collision

#endif // COLLISION_H
