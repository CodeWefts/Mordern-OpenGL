#include <vec3.h>


// --------------------- Operator ---------------------------------------
ostream& operator<<(ostream& stream, const Vector3& vector)
{
	stream << "\n";
	for (int i = 0; i < 3; i++)
	{
		stream << vector.value[i] << " ";

	}
	stream << "\n";
	return stream;
}

Vector3 Vector3::operator+(const Vector3& vector2)
{
	Vector3 sumVector;

	for (int i = 0; i < 3; i++)
		sumVector.value[i] = this->value[i] + vector2.value[i];

	return sumVector;
}

Vector3 Vector3::operator-(const Vector3& vector2)
{
	Vector3 sumVector;

	for (int i = 0; i < 3; i++)
		sumVector.value[i] = this->value[i] - vector2.value[i];

	return sumVector;
}

// ------------------------ Function --------------------------------------

float Vector3::normVector()
{
	float sum;

	for (int i = 0; i < 3; i++)
	{
		sum += pow(this->value[i], 2);
	}

	float norm = sqrt(sum);
	cout << "NORM : " << norm;
	cout << "\n";

	return norm;
}

Vector3 Vector3::oppositeVector()
{
	for (int i = 0; i < 3; i++)
		this->value[i] = -this->value[i];

	cout << "OPPOSITE VECTOR : " << *this << endl;
	return *this;
}

float Vector3::scalarVector(Vector3 vector1)
{
	float scalarVector = 0;

	for (int i = 0; i < 3; i++)
		scalarVector += vector1.value[i] * this->value[i];

	return scalarVector;
}

float Vector3::angleVector(Vector3 vector1)
{

	return (acosf(scalarVector(vector1) / (vector1.normVector() * this->normVector()))) * (180 / M_PI);
}

Vector3 Vector3::crossVector3(Vector3 vector1)
{
	Vector3 v1;
	v1.value[0] = vector1.value[1] * this->value[2] - vector1.value[2] * this->value[1];
	v1.value[1] = vector1.value[2] * this->value[0] - vector1.value[0] * this->value[2];
	v1.value[2] = vector1.value[0] * this->value[1] - vector1.value[1] * this->value[0];

	return v1;
}

float Vector3::distVector(Vector3 vector1)
{
	Vector3 vec = *this - vector1;

	return vec.normVector();
}


// ----------------------------- Builder -------------------------------
Vector3::Vector3()
{
	for (int i = 0; i < 3; i++)
	{
		this->value.push_back(0.f);
	}
}

