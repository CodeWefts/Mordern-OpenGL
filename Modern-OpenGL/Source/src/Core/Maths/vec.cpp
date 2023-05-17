#include <vec.h>

// --------------------- Operator ---------------------------------------
ostream& operator<<(ostream& stream, const Vector& vector)
{
	stream << "\n";
	for (int i = 0; i < vector.size; i++)
	{
		stream << vector.value[i] << " ";

	}
	stream << "\n";
	return stream;
}
Vector Vector::operator+(const Vector& vector2)
{
	assert(this->size == this->size);
	Vector sumVector(this->size);

	for (int i = 0; i < this->size; i++)
		sumVector.value[i] = this->value[i] + this->value[i];

	return sumVector;
}
Vector Vector::operator-(const Vector& vector2)
{
	assert(this->size == this->size);
	Vector sumVector(this->size);

	for (int i = 0; i < this->size; i++)
		sumVector.value[i] = this->value[i] - this->value[i];

	return sumVector;
}

// ------------------------ Function --------------------------------------

float Vector::normVector()
{
	float sum = pow(this->value[0], 2);

	for (int i = 1; i < this->size; i++)
	{
		sum += pow(this->value[i], 2);
	}

	float norm = sqrt(sum);
	cout << "NORM : " << norm;
	cout << "\n";

	return norm;
}

Vector Vector::oppositeVector()
{
	for (int i = 0; i < this->size; i++)
		this->value[i] = -this->value[i];

	cout << "OPPOSITE VECTOR : " << *this << endl;
	return *this;
}

float Vector::scalarVector(Vector vector1)
{
	assert(vector1.size == this->size);
	float scalarVector = 0;

	for (int i = 0; i < vector1.size; i++)
		scalarVector += vector1.value[i] * this->value[i];

	return scalarVector;
}

float Vector::angleVector(Vector vector1)
{
	return (acosf(this->scalarVector(vector1) / (vector1.normVector() * this->normVector()))) * (180 / M_PI);
}

float Vector::crossVector2(Vector vector1)
{
	assert(vector1.size == this->size);
	assert(vector1.size == 2);
	return vector1.value[0] * this->value[1] - vector1.value[1] * this->value[0];

}

Vector Vector::crossVector3(Vector vector1)
{
	assert(vector1.size == this->size);
	assert(vector1.size == 3);

	Vector v1(vector1.size);
	v1.value[0] = vector1.value[1] * this->value[2] - vector1.value[2] * this->value[1];
	v1.value[1] = vector1.value[2] * this->value[0] - vector1.value[0] * this->value[2];
	v1.value[2] = vector1.value[0] * this->value[1] - vector1.value[1] * this->value[0];

	return v1;
}

float Vector::distVector(Vector vector1)
{
	
	assert(vector1.size == this->size);

	Vector vec = *this - vector1;

	return vec.normVector();
}


// ----------------------------- Builder -------------------------------

Vector::Vector(int size)
{
	this->size = size;

	for (int i = 0; i < size; i++)
	{
		this->value.push_back(0.f);
	}
}
