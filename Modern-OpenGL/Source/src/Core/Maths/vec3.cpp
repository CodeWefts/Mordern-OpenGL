#include <vec3.h>

Vector3::Vector3()
	: x(0), y(0), z(0)
{
}

Vector3::Vector3(float x, float y, float z)
	: x(x), y(y), z(z)
{

}

Vector3::Vector3(float xyz)
	: x(xyz), y(xyz), z(xyz)
{

}

Vector3 Vector3::Normalize() const
{
	float norm = normVector();
	if (norm == 0)
	{
		return Vector3(0, 0, 0);
	}
	return Vector3(x / norm, y / norm, z / norm);
}

float& Vector3::operator[](int i)
{
	assert(i >= 0 && i <= 3 && "Vector 3 subscript out of range");

	return (&x)[i];
}

float Vector3::operator[](int i) const
{
	assert(i >= 0 && i <= 3 && "Vector 3 subscript out of range");

	return (&x)[i];
}

bool operator==(const Vector3& vx1, const Vector3& vx2)
{
	return vx1 == vx2;
}

double Vector3::normVector() const
{
	double norm = 0;
	norm = (x * x) + (y * y) + (z * z);
	return sqrt(norm);
}

Vector3 Vector3::operator-(const Vector3& vector) const
{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 Vector3::operator+(const Vector3& vector)
{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 Vector3::operator*(const float number) const
{
	return Vector3(x * number, y * number, z * number);
}

Vector3 Vector3::CrossProduct(Vector3 a, Vector3 b)
{
	float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;
	return Vector3(x, y, z);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

float Vector3::DotProduct(const Vector3& a, const Vector3& b)
{
	float result = a.x * b.x + a.y * b.y + a.z * b.z;
	return result;
}

Vector3 Vector3::operator*(const Vector3& vec) const
{
	return Vector3(vec.x * x, vec.y * y, vec.z * z);
}
