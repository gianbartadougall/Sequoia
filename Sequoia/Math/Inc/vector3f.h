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
#ifndef VECTOR3F_H
#define VECTOR3F_H

/* Public Includes */

/* GLEW Includes */

/* Private Includes */

/* Public Macros */

/* Public Enumerations and Structures */

namespace vector3f {

	class Vector3f {

		public:
		float v[3];

		Vector3f();
		Vector3f(float x, float y, float z);
		~Vector3f();

		void set(float xi, float yi, float zi);
		void add(float xi, float yi, float zi);
		void subtract(Vector3f v);
		float dot(Vector3f v);
	};
} // namespace vector3f

#endif // VECTOR3F_H