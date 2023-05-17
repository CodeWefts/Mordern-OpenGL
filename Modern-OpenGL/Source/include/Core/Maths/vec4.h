#pragma once

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

using namespace std;

class Vector4
{
private:

public:

	vector<float> value;
	Vector4();

	friend ostream& operator<<(ostream& stream, const Vector4& vector);
	Vector4 operator+(const Vector4& vector2);
	Vector4 operator-(const Vector4& vector2);

	float normVector();
	Vector4 oppositeVector();
	float scalarVector(Vector4 vector1);
	float angleVector(Vector4 vector1);
	float distVector(Vector4 vector1);

};
