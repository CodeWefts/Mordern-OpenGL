#include <mat4.h>

#include <assert.h>

using namespace std;


// ---------------- Operator -----------------------------

ostream& operator<<(ostream& stream, const Matrix4x4& matrix)
{
    for (int i = 0; i < 4; i++)
    {
        stream << "" << endl;
        for (int j = 0; j < 4; j++)
            stream << matrix.value[i][j] << " ";
    }
    stream << "" << endl;
    return stream;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& matrix)
{

    Matrix4x4 multipMatrix;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                multipMatrix.value[i][j] = multipMatrix.value[i][j] + (this->value[i][k] * matrix.value[k][j]);
            }
        }
    }

    return multipMatrix;
}

Vector4 Matrix4x4::operator*(const Vector4& vect)
{
    Vector4 multipMatrix;

    for (int j = 0; j < 4; j++)
    {
        for (int k = 0; k < 4; k++)
        {
            multipMatrix[j] = multipMatrix[j] + (this->value[j][k] * vect[k]);
        }
    }

    return multipMatrix;
}



// ----------------- Function -----------------------------

Matrix4x4 Matrix4x4::IdentityMatrix()
{

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                this->value[i][j] = 1;

            else
                this->value[i][j] = 0;

        }

    return *this;
}
Matrix4x4 Matrix4x4::Diag(float_t value)
{

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
                this->value[i][j] = value;

            else
                this->value[i][j] = 0;

        }

    return *this;
}

Matrix4x4 Matrix4x4::translateMatrix(Vector3& vec)
{
    Matrix4x4 newMatrix;
    newMatrix.IdentityMatrix();
    for (int j = 0; j < 3; j++)
    {
        newMatrix.value[j][3] = vec[j];
    }

    this->value = (newMatrix * *this).value;

    return *this;
}


Matrix4x4 Matrix4x4::rotate(float_t x, float_t y, float_t z, float_t angle)
{
    Matrix4x4 newMatrix;
    newMatrix.IdentityMatrix();

    newMatrix.value =
    {
        {x * x * (1 - cosf(angle)) + cosf(angle), y * x * (1 - cosf(angle)) - z * sinf(angle), z * x * (1 - cosf(angle)) + y * sinf(angle),0} ,
        {x * y * (1 - cosf(angle)) + z * sinf(angle), y * y * (1 - cosf(angle)) + cosf(angle), z * y * (1 - cosf(angle)) - x * sinf(angle),0} ,
        {x * z * (1 - cosf(angle)) - y * sinf(angle), y * z * (1 - cosf(angle)) + x * sinf(angle), z * z * (1 - cosf(angle)) + cosf(angle),0},
        {0,0,0,1}
    };

    this->value = (*this * newMatrix).value;
    return *this;
}

Matrix4x4 Matrix4x4::rotate(float angle, Vector3& vec)
{
    Matrix4x4 newMatrix;
    newMatrix.IdentityMatrix();

    newMatrix.value =
    {
        {vec.x * vec.x * (1 - cosf(angle)) + cosf(angle), vec.y * vec.x * (1 - cosf(angle)) - vec.z * sinf(angle), vec.z * vec.x * (1 - cosf(angle)) + vec.y * sinf(angle),0} ,
        {vec.x * vec.y * (1 - cosf(angle)) + vec.z * sinf(angle), vec.y * vec.y * (1 - cosf(angle)) + cosf(angle), vec.z * vec.y * (1 - cosf(angle)) - vec.x * sinf(angle),0} ,
        {vec.x * vec.z * (1 - cosf(angle)) - vec.y * sinf(angle), vec.y * vec.z * (1 - cosf(angle)) + vec.x * sinf(angle), vec.z * vec.z * (1 - cosf(angle)) + cosf(angle),0},
        {0,0,0,1}
    };

    this->value = (*this * newMatrix).value;

    return *this;
}

Matrix4x4 Matrix4x4::TRS(Vector3& angle, Vector3& vectorTrans, Vector3& vectorScaling, Vector3& axes)
{
    Matrix4x4 rotation;
    Matrix4x4 R;
    Matrix4x4 S;
    Matrix4x4 T;

    //TRANSLATE
    T.IdentityMatrix();
    T.value[0][3] = vectorTrans[0];
    T.value[1][3] = vectorTrans[1];
    T.value[2][3] = vectorTrans[2];

    //ROTATION
    Matrix4x4 rX, rY, rZ;
    rX = rotate(axes[0], 0, 0, angle[0]);
    rY = rotate(0, axes[1], 0, angle[1]);
    rZ = rotate(0, 0, axes[2], angle[2]);

    rotation = rZ * (rY * rX);

    R.value =
    {
        {rotation.value[0][0], rotation.value[0][1], rotation.value[0][2], 0},
        {rotation.value[1][0], rotation.value[1][1], rotation.value[1][2], 0},
        {rotation.value[2][0] ,rotation.value[2][1], rotation.value[2][2], 0},
        {0,0,0,1}
    };

    //SCALING
    S.IdentityMatrix();
    S.value[0][0] = vectorScaling[0];
    S.value[1][1] = vectorScaling[1];
    S.value[2][2] = vectorScaling[2];

    return (T * R) * S;
}

Matrix4x4 Matrix4x4::Perspective(const float& fov, const float& aspect, const float& near, const float& far)
{
    const float tanHalfFov = tan(fov / 2.f);

    Matrix4x4 projMatrix;

    projMatrix.value = {
        { 1 / (aspect * tanHalfFov), 0, 0, 0 },
        { 0, 1 / tanHalfFov, 0, 0 },
        { 0, 0, -(far + near) / (far - near), -(2 * far * near) / (far - near) },
        { 0, 0, -1, 0 }
    };


    this->value = projMatrix.value;

    return *this;
}

Matrix4x4 Matrix4x4::scale(Vector3& vector)
{
    Matrix4x4 newMatrix;
    newMatrix.value = {
        {vector.x, 0, 0, 0},
        {0 ,vector.y, 0, 0}, 
        {0,0,vector.z, 0},
        {0,0,0,1}
    };

    this->value = (*this * newMatrix).value;

    return *this;
}

float* Matrix4x4::Array()
{
    float array[] = {
        value[0][0], value[0][1], value[0][2], value[0][3],
        value[1][0], value[1][1], value[1][2], value[1][3],
        value[2][0], value[2][1], value[2][2], value[2][3],
        value[3][0], value[3][1], value[3][2], value[3][3]
    };

    return array;
}

// ------------------- Builder ------------------------

Matrix4x4::Matrix4x4()
{
    for (int i = 0; i < 4; i++)
        this->value.push_back(vector<float>(4, 0.f));
}