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
#include <math.h>
#include <stdio.h>

/* GLEW Includes */

/* Private Includes */
#include "camera.h"
#include "mathUtils.h"

/* Private Macros */
#define CAMERA_TRANSLATION_SPEED 0.0005
#define CAMERA_ROTATION_SPEED	 (0.4 / 90)

/* Private Enumerations and Structures */

using namespace camera;
using namespace mathUtils;

Camera::Camera() {
	iUnitVector.set(1, 0, 0);
	jUnitVector.set(0, 1, 0);
	kUnitVector.set(0, 0, 1);
}

Camera::~Camera() {}

void Camera::translate(Vector3f translation) {
	this->position.add(translation);
}

void Camera::rotate(Vector3f rotation) {
	this->rotation.add(rotation);
}

/* Need to fix up the movement so it moves correctly based on what direction
	the camera is currently facing in !*/
void Camera::move_left() {
	this->position.add_x(CAMERA_TRANSLATION_SPEED * cos(this->rotation.v[1]));
	// this->position.add_x(CAMERA_TRANSLATION_SPEED * cos(this->rotation.v[1]));
	// this->position.add_z(CAMERA_TRANSLATION_SPEED * sin(this->rotation.v[1]));
}

void Camera::move_right() {
	this->position.add_x(-CAMERA_TRANSLATION_SPEED * cos(this->rotation.v[1]));
	// this->position.add_x(-CAMERA_TRANSLATION_SPEED * cos(this->rotation.v[1]));
	// this->position.add_y(-CAMERA_TRANSLATION_SPEED * sin(this->rotation.v[1]));
}

void Camera::move_forward() {
	this->position.add_z(CAMERA_TRANSLATION_SPEED * cos(this->rotation.v[1]));
	this->position.add_x(-CAMERA_TRANSLATION_SPEED * sin(this->rotation.v[1]));
}

void Camera::move_backward() {
	this->position.add_z(-CAMERA_TRANSLATION_SPEED * cos(this->rotation.v[1]));
	this->position.add_x(CAMERA_TRANSLATION_SPEED * sin(this->rotation.v[1]));
}

void Camera::rotate_left() {

	// Calculate the vector to the left of the cameras current direction
	Vector3f dir	 = Vector3f(cos(this->rotation.x()), sin(this->rotation.y()), -sin(this->rotation.x())));
	Vector3f leftDir = Vector3f::cross(jUnitVector, dir);

	this->rotation.add_y(CAMERA_ROTATION_SPEED);

	if ((this->rotation).v[1] > (PI_MULT_2)) {
		this->rotation.add_y(-PI_MULT_2);
	}
	printf("Theta: %f\r\n", RAD_TO_DEG(this->rotation.v[1]));
}

void Camera::rotate_right() {
	this->rotation.add_y(-CAMERA_ROTATION_SPEED);

	if ((this->rotation).v[1] < 0) {
		this->rotation.add_y(PI_MULT_2);
	}

	printf("Theta: %f\r\n", RAD_TO_DEG(this->rotation.v[1]));
}

/* I don't understand why you need to change the sign of the camera rotation
	in the vertical position based on the z-axis but you do if you want the
	camera rotation to work correctly when the camera moves around z = 0*/
void Camera::rotate_up() {

	// Cannot rotate above 180 degrees
	if (this->rotation.v[0] < PI_DIV_2) {
		this->rotation.add_x(CAMERA_ROTATION_SPEED);
		printf("Phi: %f\r\n", RAD_TO_DEG(this->rotation.v[0]));

		if ((this->rotation).v[0] > PI_DIV_2) {
			this->rotation.set_x(PI_DIV_2);
		}
	}
}

/* I don't understand why you need to change the sign of the camera rotation
	in the vertical position based on the z-axis but you do if you want the
	camera rotation to work correctly when the camera moves around z = 0*/
void Camera::rotate_down() {

	if (this->rotation.v[0] > -PI_DIV_2) {
		this->rotation.add_x(-CAMERA_ROTATION_SPEED);
		printf("Phi: %f\r\n", RAD_TO_DEG(this->rotation.v[0]));

		if (this->rotation.v[0] < -PI_DIV_2) {
			this->rotation.set_x(-PI_DIV_2);
		}
	}
}