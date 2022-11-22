#include <iostream>
#include "vector4f.h"

using namespace vector4f;

Vector4f::Vector4f() {
	x = 0;
	y = 0;
	z = 0;
}

Vector4f::~Vector4f() {}

Vector4f::Vector4f(float xi, float yi, float zi) {
	x = xi;
	y = yi;
	z = zi;
}

void Vector4f::add(float xi, float yi, float zi) {
	x += xi;
	y += yi;
	z += zi;
}

// void Vector4f::add(Vector4f v) {
// 	x += v.x;
// 	y += v.y;
// 	z += v.z;
// }

void Vector4f::subtract(Vector4f v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

float Vector4f::dot(Vector4f v) {
	return (x * v.x) + (y * v.y) + (z * v.z);
}