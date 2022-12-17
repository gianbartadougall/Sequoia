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

/* Public Includes */

/* GLEW Includes */

/* Private Includes */
#include "camera.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace camera;

Camera::Camera() {}

Camera::~Camera() {}

void Camera::translate(Vector3f translation) {
	this->position.add(translation);
}

void Camera::rotate(Vector3f rotation) {
	this->rotation.add(rotation);
}
