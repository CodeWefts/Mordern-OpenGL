#pragma once

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

using namespace std;

class Vector4
{
public:

	float x;
	float y;
	float z;
	float w;

	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(float wxyz);
	float& operator[](int i);
	Vector4 operator*(const Vector4& vec);
	Vector4 operator*(const float x);
	float operator[](int i) const;
};