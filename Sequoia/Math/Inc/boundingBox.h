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
#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

/* Public Includes */

/* GLEW Includes */

/* Private Includes */

/* Public Macros */

/* Public Enumerations and Structures */

namespace boundingBox {

	class BoundingBox {

		// Private variables
		protected:
		float minX = 100000;
		float minY = 100000;
		float minZ = 100000;
		float maxX = -100000;
		float maxY = -100000;
		float maxZ = -100000;

		public:
		BoundingBox();
		BoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
		~BoundingBox();

		void set(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
		int collision(BoundingBox* box);
		float volume();
		float length();
	};
} // namespace boundingBox

#endif // BOUNDING_BOX_H
