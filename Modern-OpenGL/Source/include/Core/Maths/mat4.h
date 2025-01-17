#pragma once
#include <vector>
#include <iostream>

#include <vec4.h>
#include <vec3.h>

using namespace std;

class Matrix4x4
{
public:

	vector<vector<float>> value;

	Matrix4x4();

	friend ostream& operator<<(ostream& stream, const Matrix4x4& matrix);
	Matrix4x4 operator*(const Matrix4x4& matrix);
	Vector4 operator*(const Vector4& vect);

	Matrix4x4 IdentityMatrix();
	Matrix4x4 Diag(float_t value);
	Matrix4x4 translateMatrix(Vector3& vec);
	Matrix4x4 rotate(float_t x, float_t y, float_t z, float_t angle);
	Matrix4x4 rotate(float time, Vector3& vec);
	Matrix4x4 TRS(Vector3& angle, Vector3& vectorTrans, Vector3& vectorScaling, Vector3& axes);
	Matrix4x4 Perspective(const float& fov, const float& aspect, const float& near, const float& far);
	Matrix4x4 scale(Vector3& vector);
	float* Array();
};
