#include <iostream>
#include <cmath>

#include "matrix4f.h"
#include "vector4f.h"

using namespace matrix4f;
using namespace vector4f;

// void Matrix4f::add(Matrix4f* m1) {

// 	m[0][0] += m1->m[0][0];
// 	m[0][1] += m1->m[0][1];
// 	m[0][2] += m1->m[0][2];
// 	m[0][3] += m1->m[0][3];

// 	m[1][0] += m1->m[1][0];
// 	m[1][1] += m1->m[1][1];
// 	m[1][2] += m1->m[1][2];
// 	m[1][3] += m1->m[1][3];

// 	m[2][0] += m1->m[2][0];
// 	m[2][1] += m1->m[2][1];
// 	m[2][2] += m1->m[2][2];
// 	m[2][3] += m1->m[2][3];

// 	m[3][0] += m1->m[3][0];
// 	m[3][1] += m1->m[3][1];
// 	m[3][2] += m1->m[3][2];
// 	m[3][3] += m1->m[3][3];
// }

// void Matrix4f::subtract(Matrix4f* m1) {

// 	m[0][0] -= m1->m[0][0];
// 	m[0][1] -= m1->m[0][1];
// 	m[0][2] -= m1->m[0][2];
// 	m[0][3] -= m1->m[0][3];

// 	m[1][0] -= m1->m[1][0];
// 	m[1][1] -= m1->m[1][1];
// 	m[1][2] -= m1->m[1][2];
// 	m[1][3] -= m1->m[1][3];

// 	m[2][0] -= m1->m[2][0];
// 	m[2][1] -= m1->m[2][1];
// 	m[2][2] -= m1->m[2][2];
// 	m[2][3] -= m1->m[2][3];

// 	m[3][0] -= m1->m[3][0];
// 	m[3][1] -= m1->m[3][1];
// 	m[3][2] -= m1->m[3][2];
// 	m[3][3] -= m1->m[3][3];
// }

Matrix4f::~Matrix4f() {}

Matrix4f::Matrix4f() {
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;

	m[4] = 0;
	m[5] = 1;
	m[6] = 0;
	m[7] = 0;

	m[8]  = 0;
	m[9]  = 0;
	m[10] = 1;
	m[11] = 0;

	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

Matrix4f::Matrix4f(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9,
				   float a10, float a11, float a12, float a13, float a14, float a15) {

	m[0] = a0;
	m[1] = a1;
	m[2] = a2;
	m[3] = a3;

	m[4] = a4;
	m[5] = a5;
	m[6] = a6;
	m[7] = a7;

	m[8]  = a8;
	m[9]  = a9;
	m[10] = a10;
	m[11] = a11;

	m[12] = a12;
	m[13] = a13;
	m[14] = a14;
	m[15] = a15;
}

void Matrix4f::rotatex(float theta) {
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;

	m[4] = 0;
	m[5] = cos(theta);
	m[6] = -sin(theta);
	m[7] = 0;

	m[8]  = 0;
	m[9]  = sin(theta);
	m[10] = cos(theta);
	m[11] = 0;

	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

void Matrix4f::rotatey(float theta) {
	m[0] = cos(theta);
	m[1] = 0;
	m[2] = sin(theta);
	m[3] = 0;

	m[4] = 0;
	m[5] = 1;
	m[6] = 0;
	m[7] = 0;

	m[8]  = -sin(theta);
	m[9]  = 0;
	m[10] = cos(theta);
	m[11] = 0;

	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

void Matrix4f::qrotx(float theta) {
	float ct  = cos(0.01);
	float ct2 = ct * ct;

	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;

	m[4] = 0;
	m[5] = -1;
	m[6] = -2 * ct;
	m[7] = 0;

	m[8]  = 0;
	m[9]  = 2 * ct;
	m[10] = -1;
	m[11] = 0;

	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

void Matrix4f::qroty(float theta) {

	m[0] = cos(theta);
	m[1] = 0;
	m[2] = -sin(theta);
	m[3] = 0;

	m[4] = 0;
	m[5] = cos(theta);
	m[6] = 0;
	m[7] = sin(theta);

	m[8]  = sin(theta);
	m[9]  = 0;
	m[10] = cos(theta);
	m[11] = 0;

	m[12] = 0;
	m[13] = sin(theta);
	m[14] = 0;
	m[15] = cos(theta);
}

void Matrix4f::qrotz(float theta) {

	m[0] = cos(theta);
	m[1] = 0;
	m[2] = 0;
	m[3] = -sin(theta);

	m[4] = 0;
	m[5] = cos(theta);
	m[6] = -sin(theta);
	m[7] = 0;

	m[8]  = 0;
	m[9]  = sin(theta);
	m[10] = cos(theta);
	m[11] = 0;

	m[12] = 0;
	m[13] = sin(theta);
	m[14] = 0;
	m[15] = cos(theta);
}

void Matrix4f::rotatez(float theta) {
	m[0] = cos(theta);
	m[1] = -sin(theta);
	m[2] = 0;
	m[3] = 0;

	m[4] = sin(theta);
	m[5] = cos(theta);
	m[6] = 0;
	m[7] = 0;

	m[8]  = 0;
	m[9]  = 0;
	m[10] = 1;
	m[11] = 0;

	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

Matrix4f::Matrix4f(Vector4f p, Vector4f s, Vector4f r) {

	// Common factors
	float cosjh		   = cos(r.y) * cos(r.x);
	float coskh		   = cos(r.z) * cos(r.x);
	float cosjk		   = cos(r.y) * cos(r.z);
	float sinjcosk	   = sin(r.y) * cos(r.z);
	float sinjcosksinh = sinjcosk * sin(r.x);
	float cosjsinh	   = cos(r.y) * sin(r.x);
	float sinkcosh	   = sin(r.y) * cos(r.x);
	float sinkh		   = sin(r.z) * sin(r.x);
	float sinjkh	   = sin(r.y) * sinkh;
	float cosksinh	   = cos(r.z) * sin(r.x);
	float cosjsink	   = cos(r.y) * sin(r.z);
	float sinjciskh	   = sinjcosk * cos(r.x);
	float sinjkcosh	   = sin(r.y) * sinkcosh;
	float SjkCh_p_CkSh = sinjkcosh + cosksinh;
	float Skh_m_SjCkh  = sinkh - sinjciskh;
	float Ckh_m_Sjkh   = coskh - sinjkh;

	m[0] = s.x * cosjk;
	m[1] = -s.y * cosjsink;
	m[2] = s.z * sin(r.y);
	m[3] = (p.x * s.x * cosjk) + (s.z * p.z * sin(r.y)) - (s.y * p.y * cosjsink);

	m[4] = s.x * (sinjcosksinh + (sinkcosh));
	m[5] = s.y * Ckh_m_Sjkh;
	m[6] = -s.z * cosjsinh;
	m[7] = (p.x * s.x * (sinjcosksinh + sinkcosh)) + (s.y * p.y * Ckh_m_Sjkh) - (s.z * p.z * cosjsinh);

	m[8]  = s.x * Skh_m_SjCkh;
	m[9]  = s.y * SjkCh_p_CkSh;
	m[10] = s.z * cosjh;
	m[11] = (p.x * s.x * Skh_m_SjCkh) + (s.y * p.y * SjkCh_p_CkSh) + (s.z * p.z * cosjh);

	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

void Matrix4f::projection_matrix(float height, float width, float far, float near) {
	float FOV		  = 70.0f;
	float aspectRatio = width / height;
	float top		  = tan(FOV * 0.5) * near;
	float bottom	  = -top;
	float right		  = top * aspectRatio;
	float left		  = -right;

	m[0] = (2 * near) / (right - left);
	m[1] = 0;
	m[2] = (right + left) / (right - left);
	m[3] = 0;

	m[4] = 0;
	m[5] = (2 * near) / (top - bottom);
	m[6] = (top + bottom) / (top - bottom);
	m[7] = 0;

	m[8]  = 0;
	m[9]  = 0;
	m[10] = -(far + near) / (far - near);
	m[11] = -(2 * far * near) / (far - near);

	m[12] = 0;
	m[13] = 0;
	m[14] = -1;
	m[15] = 0;
}

void Matrix4f::transform(Vector4f p, Vector4f s, Vector4f r) {

	Matrix4f transformation(p, s, r);
	multiply(&transformation);
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

	m[0] = matrix.m[0];
	m[1] = matrix.m[1];
	m[2] = matrix.m[2];
	m[3] = matrix.m[3];

	m[4] = matrix.m[4];
	m[5] = matrix.m[5];
	m[6] = matrix.m[6];
	m[7] = matrix.m[7];

	m[8]  = matrix.m[8];
	m[9]  = matrix.m[9];
	m[10] = matrix.m[10];
	m[11] = matrix.m[11];

	m[12] = matrix.m[12];
	m[13] = matrix.m[13];
	m[14] = matrix.m[14];
	m[15] = matrix.m[15];
}

void Matrix4f::print() {
	printf("(%f %f %f %f\r\n %f %f %f %f\r\n %f %f %f %f\r\n %f %f %f %f)\r\n", m[0], m[1], m[2], m[3], m[4], m[5],
		   m[6], m[7], m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
}
