#include <vec4.h>
/*

// --------------------- Operator ---------------------------------------
ostream& operator<<(ostream& stream, const Vector4& vector)
{
	stream << "\n";
	for (int i = 0; i < 4; i++)
	{
		stream << vector.value[i] << " ";

	}
	stream << "\n";
	return stream;
}

Vector4 Vector4::operator+(const Vector4& vector2)
{
	Vector4 sumVector;

	for (int i = 0; i < 4; i++)
		sumVector.value[i] = this->value[i] + vector2.value[i];

	return sumVector;
}

Vector4 Vector4::operator-(const Vector4& vector2)
{
	Vector4 sumVector;

	for (int i = 0; i < 4; i++)
		sumVector.value[i] = this->value[i] - vector2.value[i];

	return sumVector;
}

// ------------------------ Function --------------------------------------

float Vector4::normVector()
{
	float sum;

	for (int i = 0; i < 4; i++)
	{
		sum += pow(this->value[i], 2);
	}

	float norm = sqrt(sum);
	cout << "NORM : " << norm;
	cout << "\n";

	return norm;
}

Vector4 Vector4::oppositeVector()
{
	for (int i = 0; i < 4; i++)
		this->value[i] = -this->value[i];

	cout << "OPPOSITE VECTOR : " << *this << endl;
	return *this;
}

float Vector4::scalarVector(Vector4 vector1)
{
	float scalarVector = 0;

	for (int i = 0; i < 4; i++)
		scalarVector += vector1.value[i] * this->value[i];

	return scalarVector;
}

float Vector4::angleVector(Vector4 vector1)
{

	return (acosf(scalarVector(vector1) / (vector1.normVector() * this->normVector()))) * (180 / M_PI);
}


float Vector4::distVector(Vector4 vector1)
{
	Vector4 vec = *this - vector1;

	return vec.normVector();
}


// ----------------------------- Builder -------------------------------
Vector4::Vector4()
{
	for (int i = 0; i < 4; i++)
	{
		this->value.push_back(0.f);
	}
}
*/


Vector4::Vector4()
	:w(0), x(0), y(0), z(0)
{

}

Vector4::Vector4(float x, float y, float z, float w)
	:x(x), y(y), z(z), w(w)
{

}

Vector4::Vector4(float wxyz)
	:x(wxyz), y(wxyz), z(wxyz), w(wxyz)
{

}

float& Vector4::operator[](int i)
{
	assert(i >= 0 && i <= 3 && "Vector 4 subscript out of range");

	return (&x)[i];
}

float Vector4::operator[](int i) const
{
	assert(i >= 0 && i <= 3 && "Vector 4 subscript out of range");

	return (&x)[i];
}

Vector4 Vector4::operator*(const Vector4& vec)
{
	return Vector4(vec.x * x, vec.y * y, vec.z * z, vec.w * w);
}

Vector4 Vector4::operator*(const float x)
{
	return Vector4(this->x * x, this->y * y, this->z * z, this->w * w);
}