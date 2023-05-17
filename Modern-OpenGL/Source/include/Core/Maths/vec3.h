#pragma once

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

using namespace std;

class Vector3
{
private:

public:

	vector<float> value;
	Vector3();

	friend ostream& operator<<(ostream& stream, const Vector3& vector);
	Vector3 operator+(const Vector3& vector2);
	Vector3 operator-(const Vector3& vector2);

	float normVector();
	Vector3 oppositeVector();
	float scalarVector(Vector3 vector1);
	float angleVector(Vector3 vector1);
	Vector3 crossVector3(Vector3 vector1);
	float distVector(Vector3 vector1);

};
