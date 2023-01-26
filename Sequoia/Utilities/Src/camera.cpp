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

/* C Library Includes */
#include <math.h>
#include <stdio.h>

/* GLEW Includes */

/* Personal Includes */
#include "camera.h"
#include "mathUtils.h"
#include "strUtils.h"

/* Private Macros */
#define CAMERA_TRANSLATION_SPEED 0.0005
#define CAMERA_ROTATION_SPEED	 (0.4 / 90)

/* Private Enumerations and Structures */

using namespace camera;
using namespace mathUtils;
using namespace strUtils;

Camera::Camera() {
	iUnitVector.set(1, 0, 0);
	jUnitVector.set(0, 1, 0);
	kUnitVector.set(0, 0, 1);
	jUnitVectorNeg.set(0, -1, 0);
	rotation.set(0, 0, 0);
	position.set(0, 0, 0);
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

	this->position.add_z(CAMERA_TRANSLATION_SPEED * cos(this->rotation.v[1] - PI_DIV_2));
	this->position.add_x(CAMERA_TRANSLATION_SPEED * sin(this->rotation.v[1] - PI_DIV_2));
}

void Camera::move_right() {

	this->position.add_z(CAMERA_TRANSLATION_SPEED * cos(this->rotation.v[1] + PI_DIV_2));
	this->position.add_x(CAMERA_TRANSLATION_SPEED * sin(this->rotation.v[1] + PI_DIV_2));
}

void Camera::move_forward() {
	this->position.add_x(-CAMERA_TRANSLATION_SPEED * sin(this->rotation.v[1]));
	this->position.add_z(-CAMERA_TRANSLATION_SPEED * cos(this->rotation.v[1]));
}

void Camera::move_backward() {
	this->position.add_x(CAMERA_TRANSLATION_SPEED * sin(this->rotation.v[1]));
	this->position.add_z(CAMERA_TRANSLATION_SPEED * cos(this->rotation.v[1]));
}

void Camera::rotate_left() {

	this->rotation.add_y(CAMERA_ROTATION_SPEED);

	if ((this->rotation).v[1] > (PI_MULT_2)) {
		this->rotation.set_y(0);
	}
}

void Camera::rotate_right() {

	this->rotation.add_y(-CAMERA_ROTATION_SPEED);

	if ((this->rotation).v[1] < 0) {
		this->rotation.set_y(PI_MULT_2);
	}
}

void Camera::rotate_up() {

	if ((this->rotation).v[0] < PI_DIV_2) {
		this->rotation.add_x(CAMERA_ROTATION_SPEED);
	}
}

void Camera::rotate_down() {

	if ((this->rotation).v[0] > -PI_DIV_2) {
		this->rotation.add_x(-CAMERA_ROTATION_SPEED);
	}
}

void Camera::load_state(string line) {

	string data[6];
	StrUtils::split_string(line, data, 0, ',');

	this->position.set_x(stof(data[1]));
	this->position.set_y(stof(data[2]));
	this->position.set_z(stof(data[3]));

	this->rotation.set_x(stof(data[4]));
	this->rotation.set_y(stof(data[5]));
}