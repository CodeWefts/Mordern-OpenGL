#pragma once

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

using namespace std;

class Vector2
{
private:

public:

	vector<float> value;
	Vector2();

	friend ostream& operator<<(ostream& stream, const Vector2& vector);
	Vector2 operator+(const Vector2& vector2);
	Vector2 operator-(const Vector2& vector2);

	float normVector();
	Vector2 oppositeVector();
	float scalarVector(Vector2 vector1);
	float angleVector(Vector2 vector1);
	float crossVector2(Vector2 vector1);
	float distVector(Vector2 vector1);

};