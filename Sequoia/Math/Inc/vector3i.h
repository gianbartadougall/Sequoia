/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for int3f
 * @version 0.1
 * @date Sat Jan 07 20:48:53 2023

 *
 * @copyright Copyright (c)
 *
 */
#ifndef VECTOR3I_H
#define VECTOR3I_H

/* Public Includes */

/* GLEW Includes */

/* Private Includes */

/* Public Macros */

/* Public Enumerations and Structures */

namespace vector3i {

	class Vector3i {

		public:
		int v[3];

		Vector3i();
		Vector3i(int x, int y, int z);
		~Vector3i();

		void set(int x, int y, int z);
		void set_x(int x);
		void set_y(int y);
		void set_z(int z);
	};
} // namespace vector3i

#endif // VECTOR3I_H
