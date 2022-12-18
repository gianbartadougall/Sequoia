#include <iostream>
#include <cmath>

#include "matrix4f.h"
#include "vector4f.h"

using namespace matrix4f;
using namespace vector4f;

void Matrix4f::scale(Vector3f scalar) {
	scale(scalar.v[0], scalar.v[1], scalar.v[2]);
}

void Matrix4f::scale(float sx, float sy, float sz) {
	this->m[0] = sx;
	this->m[1] = 0;
	this->m[2] = 0;
	this->m[3] = 0;

	this->m[4] = 0;
	this->m[5] = sy;
	this->m[6] = 0;
	this->m[7] = 0;

	this->m[8]	= 0;
	this->m[9]	= 0;
	this->m[10] = sz;
	this->m[11] = 0;

	this->m[12] = 0;
	this->m[13] = 0;
	this->m[14] = 0;
	this->m[15] = 1;
}

Matrix4f::~Matrix4f() {}

Matrix4f::Matrix4f() {
	this->m[0] = 1;
	this->m[1] = 0;
	this->m[2] = 0;
	this->m[3] = 0;

	this->m[4] = 0;
	this->m[5] = 1;
	this->m[6] = 0;
	this->m[7] = 0;

	this->m[8]	= 0;
	this->m[9]	= 0;
	this->m[10] = 1;
	this->m[11] = 0;

	this->m[12] = 0;
	this->m[13] = 0;
	this->m[14] = 0;
	this->m[15] = 1;
}

void Matrix4f::set_to_identity() {
	this->m[0] = 1;
	this->m[1] = 0;
	this->m[2] = 0;
	this->m[3] = 0;

	this->m[4] = 0;
	this->m[5] = 1;
	this->m[6] = 0;
	this->m[7] = 0;

	this->m[8]	= 0;
	this->m[9]	= 0;
	this->m[10] = 1;
	this->m[11] = 0;

	this->m[12] = 0;
	this->m[13] = 0;
	this->m[14] = 0;
	this->m[15] = 1;
}

Matrix4f::Matrix4f(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9,
				   float a10, float a11, float a12, float a13, float a14, float a15) {

	this->m[0] = a0;
	this->m[1] = a1;
	this->m[2] = a2;
	this->m[3] = a3;

	this->m[4] = a4;
	this->m[5] = a5;
	this->m[6] = a6;
	this->m[7] = a7;

	this->m[8]	= a8;
	this->m[9]	= a9;
	this->m[10] = a10;
	this->m[11] = a11;

	this->m[12] = a12;
	this->m[13] = a13;
	this->m[14] = a14;
	this->m[15] = a15;
}

void Matrix4f::translate(Vector3f translation) {
	translate(translation.v[0], translation.v[1], translation.v[2]);
}

void Matrix4f::translate(float x, float y, float z) {

	Matrix4f translate;
	translate.m[0]	= 1;
	translate.m[1]	= 0;
	translate.m[2]	= 0;
	translate.m[3]	= 0;
	translate.m[4]	= 0;
	translate.m[5]	= 1;
	translate.m[6]	= 0;
	translate.m[7]	= 0;
	translate.m[8]	= 0;
	translate.m[9]	= 0;
	translate.m[10] = 1;
	translate.m[11] = 0;
	translate.m[12] = x;
	translate.m[13] = y;
	translate.m[14] = z;
	translate.m[15] = 1;

	multiply(&translate);
}

void Matrix4f::rotate(float rx, float ry, float rz) {

	/* The rotation matrix for rotating along the x-axis is given by
		1	0		0		0
		0	cos(x)	-sin(x)	0
		0	sin(x)	cos(x)	0
		0	0		0		1
	*/
	Matrix4f rotationX;
	rotationX.m[0]	= 1;
	rotationX.m[1]	= 0;
	rotationX.m[2]	= 0;
	rotationX.m[3]	= 0;
	rotationX.m[4]	= 0;
	rotationX.m[5]	= cos(rx);
	rotationX.m[6]	= -sin(rx);
	rotationX.m[7]	= 0;
	rotationX.m[8]	= 0;
	rotationX.m[9]	= sin(rx);
	rotationX.m[10] = cos(rx);
	rotationX.m[11] = 0;
	rotationX.m[12] = 0;
	rotationX.m[13] = 0;
	rotationX.m[14] = 0;
	rotationX.m[15] = 1;

	/* The rotation matrix for rotating along the y-axis is given by
		cos(y)	0	sin(y)	0
		0		1	0		0
		-sin(y)	0	cos(y)	0
		0		0	0		1
	*/
	Matrix4f rotationY;
	rotationY.m[0]	= cos(ry);
	rotationY.m[1]	= 0;
	rotationY.m[2]	= sin(ry);
	rotationY.m[3]	= 0;
	rotationY.m[4]	= 0;
	rotationY.m[5]	= 1;
	rotationY.m[6]	= 0;
	rotationY.m[7]	= 0;
	rotationY.m[8]	= -sin(ry);
	rotationY.m[9]	= 0;
	rotationY.m[10] = cos(ry);
	rotationY.m[11] = 0;
	rotationY.m[12] = 0;
	rotationY.m[13] = 0;
	rotationY.m[14] = 0;
	rotationY.m[15] = 1;

	/* The rotation matrix for rotating along the z-axis is given by
		cos(z)	-sin(z)	0	0
		sin(z)	cos(z)	0	0
		0		0		1	0
		0		0		0	1
	*/
	Matrix4f rotationZ;
	rotationZ.m[0]	= cos(rz);
	rotationZ.m[1]	= -sin(rz);
	rotationZ.m[2]	= 0;
	rotationZ.m[3]	= 0;
	rotationZ.m[4]	= sin(rz);
	rotationZ.m[5]	= cos(rz);
	rotationZ.m[6]	= 0;
	rotationZ.m[7]	= 0;
	rotationZ.m[8]	= 0;
	rotationZ.m[9]	= 0;
	rotationZ.m[10] = 1;
	rotationZ.m[11] = 0;
	rotationZ.m[12] = 0;
	rotationZ.m[13] = 0;
	rotationZ.m[14] = 0;
	rotationZ.m[15] = 1;

	// Apply all rotations to the matrix of this class
	multiply(&rotationX);
	multiply(&rotationY);
	multiply(&rotationZ);
}

void Matrix4f::rotate(Vector3f rotation) {
	rotate(rotation.v[0], rotation.v[1], rotation.v[2]);
}

void Matrix4f::qrotx(float theta) {
	float ct = cos(0.01);

	this->m[0] = 1;
	this->m[1] = 0;
	this->m[2] = 0;
	this->m[3] = 0;

	this->m[4] = 0;
	this->m[5] = -1;
	this->m[6] = -2 * ct;
	this->m[7] = 0;

	this->m[8]	= 0;
	this->m[9]	= 2 * ct;
	this->m[10] = -1;
	this->m[11] = 0;

	this->m[12] = 0;
	this->m[13] = 0;
	this->m[14] = 0;
	this->m[15] = 1;
}

void Matrix4f::qroty(float theta) {

	this->m[0] = cos(theta);
	this->m[1] = 0;
	this->m[2] = -sin(theta);
	this->m[3] = 0;

	this->m[4] = 0;
	this->m[5] = cos(theta);
	this->m[6] = 0;
	this->m[7] = sin(theta);

	this->m[8]	= sin(theta);
	this->m[9]	= 0;
	this->m[10] = cos(theta);
	this->m[11] = 0;

	this->m[12] = 0;
	this->m[13] = sin(theta);
	this->m[14] = 0;
	this->m[15] = cos(theta);
}

void Matrix4f::qrotz(float theta) {

	this->m[0] = cos(theta);
	this->m[1] = 0;
	this->m[2] = 0;
	this->m[3] = -sin(theta);

	this->m[4] = 0;
	this->m[5] = cos(theta);
	this->m[6] = -sin(theta);
	this->m[7] = 0;

	this->m[8]	= 0;
	this->m[9]	= sin(theta);
	this->m[10] = cos(theta);
	this->m[11] = 0;

	this->m[12] = 0;
	this->m[13] = sin(theta);
	this->m[14] = 0;
	this->m[15] = cos(theta);
}

void Matrix4f::transform(Vector3f translation, Vector3f rotation, Vector3f scalar) {

	Matrix4f translationMatrix;
	Matrix4f rotationMatrix;
	Matrix4f scalarMatrix;

	translationMatrix.translate(translation);
	rotationMatrix.rotate(rotation);
	scalarMatrix.scale(scalar);

	this->multiply(&rotationMatrix);
	this->multiply(&scalarMatrix);
	this->multiply(&translationMatrix);
}

void Matrix4f::projection_matrix(float width, float height, float near, float far) {
	float FOV		  = 70.0f;
	float aspectRatio = width / height;
	float top		  = tan(FOV * 0.5) * near;
	float bottom	  = -top;
	float right		  = top * aspectRatio;
	float left		  = -right;

	this->m[0] = (2 * near) / (right - left);
	this->m[1] = 0;
	this->m[2] = 0;
	this->m[3] = 0;

	this->m[4] = 0;
	this->m[5] = (2 * near) / (top - bottom);
	this->m[6] = 0;
	this->m[7] = 0;

	this->m[8]	= (right + left) / (right - left);
	this->m[9]	= (top + bottom) / (top - bottom);
	this->m[10] = -(far + near) / (far - near);
	this->m[11] = -1;

	this->m[12] = 0;
	this->m[13] = 0;
	this->m[14] = -(2 * far * near) / (far - near);
	this->m[15] = 0;
}

void Matrix4f::multiply(Matrix4f* m1) {

	Matrix4f matrix;

	matrix.m[0] = (m[0] * m1->m[0]) + (m[1] * m1->m[4]) + (m[2] * m1->m[8]) + (m[3] * m1->m[12]);
	matrix.m[1] = (m[0] * m1->m[1]) + (m[1] * m1->m[5]) + (m[2] * m1->m[9]) + (m[3] * m1->m[13]);
	matrix.m[2] = (m[0] * m1->m[2]) + (m[1] * m1->m[6]) + (m[2] * m1->m[10]) + (m[3] * m1->m[14]);
	matrix.m[3] = (m[0] * m1->m[3]) + (m[1] * m1->m[7]) + (m[2] * m1->m[11]) + (m[3] * m1->m[15]);

	matrix.m[4] = (m[4] * m1->m[0]) + (m[5] * m1->m[4]) + (m[6] * m1->m[8]) + (m[7] * m1->m[12]);
	matrix.m[5] = (m[4] * m1->m[1]) + (m[5] * m1->m[5]) + (m[6] * m1->m[9]) + (m[7] * m1->m[13]);
	matrix.m[6] = (m[4] * m1->m[2]) + (m[5] * m1->m[6]) + (m[6] * m1->m[10]) + (m[7] * m1->m[14]);
	matrix.m[7] = (m[4] * m1->m[3]) + (m[5] * m1->m[7]) + (m[6] * m1->m[11]) + (m[7] * m1->m[15]);

	matrix.m[8]	 = (m[8] * m1->m[0]) + (m[9] * m1->m[4]) + (m[10] * m1->m[8]) + (m[11] * m1->m[12]);
	matrix.m[9]	 = (m[8] * m1->m[1]) + (m[9] * m1->m[5]) + (m[10] * m1->m[9]) + (m[11] * m1->m[13]);
	matrix.m[10] = (m[8] * m1->m[2]) + (m[9] * m1->m[6]) + (m[10] * m1->m[10]) + (m[11] * m1->m[14]);
	matrix.m[11] = (m[8] * m1->m[3]) + (m[9] * m1->m[7]) + (m[10] * m1->m[11]) + (m[11] * m1->m[15]);

	matrix.m[12] = (m[12] * m1->m[0]) + (m[13] * m1->m[4]) + (m[14] * m1->m[8]) + (m[15] * m1->m[12]);
	matrix.m[13] = (m[12] * m1->m[1]) + (m[13] * m1->m[5]) + (m[14] * m1->m[9]) + (m[15] * m1->m[13]);
	matrix.m[14] = (m[12] * m1->m[2]) + (m[13] * m1->m[6]) + (m[14] * m1->m[10]) + (m[15] * m1->m[14]);
	matrix.m[15] = (m[12] * m1->m[3]) + (m[13] * m1->m[7]) + (m[14] * m1->m[11]) + (m[15] * m1->m[15]);

	this->m[0] = matrix.m[0];
	this->m[1] = matrix.m[1];
	this->m[2] = matrix.m[2];
	this->m[3] = matrix.m[3];

	this->m[4] = matrix.m[4];
	this->m[5] = matrix.m[5];
	this->m[6] = matrix.m[6];
	this->m[7] = matrix.m[7];

	this->m[8]	= matrix.m[8];
	this->m[9]	= matrix.m[9];
	this->m[10] = matrix.m[10];
	this->m[11] = matrix.m[11];

	this->m[12] = matrix.m[12];
	this->m[13] = matrix.m[13];
	this->m[14] = matrix.m[14];
	this->m[15] = matrix.m[15];
}

void Matrix4f::print() {
	printf("(%f %f %f %f\r\n %f %f %f %f\r\n %f %f %f %f\r\n %f %f %f %f)\r\n", m[0], m[1], m[2], m[3], m[4], m[5],
		   m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
}