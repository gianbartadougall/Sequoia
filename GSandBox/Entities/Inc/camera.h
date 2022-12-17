/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for camera
 * @version 0.1
 * @date Sat Dec 17 13:46:07 2022

 *
 * @copyright Copyright (c)
 *
 */
#ifndef CAMERA_H
#define CAMERA_H

/* Public Includes */

/* GLEW Includes */

/* Private Includes */
#include "vector3f.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace vector3f;

namespace camera {

	class Camera {

		// Private variables

		public:
		Camera();
		~Camera();

		Vector3f position;
		Vector3f rotation;

		void translate(Vector3f translation);
		void rotate(Vector3f rotation);
	};
} // namespace camera

#endif // CAMERA_H
