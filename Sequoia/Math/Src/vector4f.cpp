#include <iostream>
#include "vector4f.h"

using namespace vector4f;

Vector4f::Vector4f() {
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	v[3] = 0;
}

Vector4f::Vector4f(float xi, float yi, float zi, float wi) {
	v[0] = xi;
	v[1] = yi;
	v[2] = zi;
	v[3] = wi;
}

Vector4f::~Vector4f() {}

void Vector4f::add(float xi, float yi, float zi, float wi) {
	v[0] += xi;
	v[1] += yi;
	v[2] += zi;
	v[3] += wi;
}

void Vector4f::subtract(float xi, float yi, float zi, float wi) {
	v[0] -= xi;
	v[1] -= yi;
	v[2] -= zi;
	v[3] -= wi;
}

void Vector4f::add(Vector4f v1) {
	v[0] += v1.v[0];
	v[1] += v1.v[1];
	v[2] += v1.v[2];
	v[3] += v1.v[3];
}

void Vector4f::subtract(Vector4f v1) {
	v[0] -= v1.v[0];
	v[1] -= v1.v[1];
	v[2] -= v1.v[2];
	v[3] -= v1.v[3];
}