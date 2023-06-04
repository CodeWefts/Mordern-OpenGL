#pragma once

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

using namespace std;



class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(float xyz);

	float& operator[](int i);
	float operator[](int i) const;
	friend bool operator==(const Vector3& vx1, const Vector3& vx2);


	Vector3 operator-(const Vector3& vector) const;
	Vector3 operator-() const;
	Vector3 operator*(const float number) const;
	Vector3 operator+(const Vector3& vector);
	Vector3 Normalize() const;
	static Vector3 CrossProduct(Vector3 a, Vector3 b);
	double normVector() const;
	static float DotProduct(const Vector3& a, const Vector3& b);
	Vector3 operator*(const Vector3& vec) const;
};
