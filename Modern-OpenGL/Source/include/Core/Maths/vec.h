#pragma once

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

using namespace std;

class Vector
{
private:

public :

	int size;
	vector<float> value;
	Vector(int size);


	friend ostream& operator<<(ostream& stream, const Vector& vector);
	Vector operator+(const Vector& vector2);
	Vector operator-(const Vector& vector2);

	float normVector();
	Vector oppositeVector();
	float scalarVector(Vector vector1);
	float angleVector(Vector vector1);
	float crossVector2(Vector vector1);
	Vector crossVector3(Vector vector1);
	float distVector(Vector vector1);
};
