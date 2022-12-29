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

		void set_x(float xi);
		void set_y(float yi);
		void set_z(float zi);
		void set(float xi, float yi, float zi);
		void set(Vector3f vector);

		void add_x(float xi);
		void add_y(float yi);
		void add_z(float zi);
		void add(float xi, float yi, float zi);
		void add(Vector3f vector);

		void subtract(Vector3f v);

		void cross(Vector3f v);

		void print();

		float x();
		float y();
		float z();

		float dot(Vector3f v);

		static Vector3f cross(Vector3f v1, Vector3f v2);
	};
} // namespace vector3f

#endif // VECTOR3F_H