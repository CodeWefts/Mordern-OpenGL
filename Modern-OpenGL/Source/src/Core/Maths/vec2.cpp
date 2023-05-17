#include <vec2.h>


// --------------------- Operator ---------------------------------------
ostream& operator<<(ostream& stream, const Vector2& vector)
{
	stream << "\n";
	for (int i = 0; i < 2; i++)
	{
		stream << vector.value[i] << " ";

	}
	stream << "\n";
	return stream;
}

Vector2 Vector2::operator+(const Vector2& vector2)
{
	Vector2 sumVector;

	for (int i = 0; i < 2; i++)
		sumVector.value[i] = this->value[i] + vector2.value[i];

	return sumVector;
}

Vector2 Vector2::operator-(const Vector2& vector2)
{
	Vector2 sumVector;

	for (int i = 0; i < 2; i++)
		sumVector.value[i] = this->value[i] - vector2.value[i];

	return sumVector;
}

// ------------------------ Function --------------------------------------

float Vector2::normVector()
{
	float sum;
	
	for (int i = 0; i < 2; i++)
	{
		sum += pow(this->value[i], 2);
	}

	float norm = sqrt(sum);
	cout << "NORM : " << norm;
	cout << "\n";

	return norm;
}

Vector2 Vector2::oppositeVector()
{
	for (int i = 0; i < 2; i++)
		this->value[i] = -this->value[i];

	cout << "OPPOSITE VECTOR : " << *this << endl;
	return *this;
}

float Vector2::scalarVector(Vector2 vector1)
{
	float scalarVector = 0;

	for (int i = 0; i < 2; i++)
		scalarVector += vector1.value[i] * this->value[i];

	return scalarVector;
}

float Vector2::angleVector(Vector2 vector1)
{

	return (acosf(scalarVector(vector1) / (vector1.normVector() * this->normVector()))) * (180 / M_PI);
}

float Vector2::crossVector2(Vector2 vector1)
{
	return vector1.value[0] * this->value[1] - vector1.value[1] * this->value[0];

}

float Vector2::distVector(Vector2 vector1)
{
	Vector2 vec = *this - vector1;

	return vec.normVector();
}


// ----------------------------- Builder -------------------------------
Vector2::Vector2()
{
	for (int i = 0; i < 2; i++)
	{
		this->value.push_back(0.f);
	}
}

