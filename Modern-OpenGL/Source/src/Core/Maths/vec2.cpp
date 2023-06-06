#include <vec2.h>

Vector2::Vector2()
	: x(0), y(0)
{
}

Vector2::Vector2(float x, float y)
	: x(x), y(y)
{

}

Vector2::Vector2(float xy)
	: x(xy), y(xy)
{

}

Vector2 Vector2::Normalize() const
{
	float norm = normVector();
	if (norm == 0)
	{
		return Vector2(0, 0);
	}
	return Vector2(x / norm, y / norm);
}

float& Vector2::operator[](int i)
{
	assert(i >= 0 && i <= 3 && "Vector 3 subscript out of range");

	return (&x)[i];
}

float Vector2::operator[](int i) const
{
	assert(i >= 0 && i <= 3 && "Vector 3 subscript out of range");

	return (&x)[i];
}

bool operator==(const Vector2& vx1, const Vector2& vx2)
{
	return vx1 == vx2;
}

double Vector2::normVector() const
{
	double norm = 0;
	norm = (x * x) + (y * y);
	return sqrt(norm);
}

Vector2 Vector2::operator-(const Vector2& vector) const
{
	return Vector2(x - vector.x, y - vector.y);
}

Vector2 Vector2::operator+(const Vector2& vector)
{
	return Vector2(x + vector.x, y + vector.y);
}

Vector2 Vector2::operator*(const float number) const
{
	return Vector2(x * number, y * number);
}

float Vector2::CrossProduct(Vector2 a, Vector2 b)
{

	return (a.x * b.y) - (a.y * b.x) ;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

float Vector2::DotProduct(const Vector2& a, const Vector2& b)
{
	float result = a.x * b.x + a.y * b.y;
	return result;
}

Vector2 Vector2::operator*(const Vector2& vec) const
{
	return Vector2(vec.x * x, vec.y * y);
}
