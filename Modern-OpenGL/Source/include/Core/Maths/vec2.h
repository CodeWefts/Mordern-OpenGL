#pragma once

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

using namespace std;



class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);
	Vector2(float xy);

	float& operator[](int i);
	float operator[](int i) const;
	friend bool operator==(const Vector2& vx1, const Vector2& vx2);


	Vector2 operator-(const Vector2& vector) const;
	Vector2 operator-() const;
	Vector2 operator*(const float number) const;
	Vector2 operator+(const Vector2& vector);
	Vector2 Normalize() const;
	static float CrossProduct(Vector2 a, Vector2 b);
	double normVector() const;
	static float DotProduct(const Vector2& a, const Vector2& b);
	Vector2 operator*(const Vector2& vec) const;
};
