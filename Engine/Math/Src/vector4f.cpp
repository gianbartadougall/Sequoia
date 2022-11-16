#include <iostream>
#include "vector4f.h"

Vector4f::Vector4f() {
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
}

void Vector4f::add(Vector4f v1) {
    v[0] += v1[0];
    v[1] += v1[1];
    v[2] += v1[2];
}

void Vector4f::subtract(Vector4f v1) {
    v[0] -= v1[0];
    v[1] -= v1[1];
    v[2] -= v1[2];
}

float Vector4f::dot(Vector4f v1) {
    return (v[0] * v1[0]) + (v[1] * v1[1]) + (v[2] * v1[2]);
}