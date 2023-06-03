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
            multipMatrix.value[j] = multipMatrix.value[j] + (this->value[j][k] * vect.value[k]);
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

Matrix4x4 Matrix4x4::translateMatrix(Vector3& vec)
{
    for (int j = 0; j < 3; j++)
    {
        this->value[j][3] = vec.value[j];
    }

    return *this;
}

Matrix4x4 Matrix4x4::transposeMatrix()
{
    Matrix4x4 trans;

    for (int j = 0; j < 4; j++)
    {
        Vector4 vec;

        for (int i = 0; i < 4; i++)
        {
            vec.value[i] = this->value[i][j];
        }

        trans.value[j] = vec.value;
        
    }
    
    this->value = trans.value;

    return *this;
}

Matrix4x4 Matrix4x4::rotate(float_t x, float_t y, float_t z, float_t angle)
{
    Matrix4x4 newMatrix;

    newMatrix.value =
    {
        {x * x * (1 - cosf(angle)) + cosf(angle), y * x * (1 - cosf(angle)) - z * sinf(angle), z * x * (1 - cosf(angle)) + y * sinf(angle)} ,
        {x * y * (1 - cosf(angle)) + z * sinf(angle), y * y * (1 - cosf(angle)) + cosf(angle), z * y * (1 - cosf(angle)) - x * sinf(angle)} ,
        {x * z * (1 - cosf(angle)) - y * sinf(angle), y * z * (1 - cosf(angle)) - x * sinf(angle), z * z * (1 - cosf(angle)) + cosf(angle)},
        {0,0,0,1}
    };

    Matrix4x4 test;
    test = *this * newMatrix;

    this->value = test.value;

    return *this;
}

Matrix4x4 Matrix4x4::rotate(float time, Vector3& vec)
{


    return *this;
}

Matrix4x4 Matrix4x4::TRS(Vector4& angle, Vector4& vectorTrans, Vector4& vectorScaling, Vector4& axes)
{
    Matrix4x4 rotation;
    Matrix4x4 R;
    Matrix4x4 S;
    Matrix4x4 T;

    //TRANSLATE
    T.IdentityMatrix();
    T.value[0][3] = vectorTrans.value[0];
    T.value[1][3] = vectorTrans.value[1];
    T.value[2][3] = vectorTrans.value[2];

    //ROTATION
    Matrix4x4 rX, rY, rZ;
    rX = rotate(axes.value[0], 0, 0, angle.value[0]);
    rY = rotate(0, axes.value[1], 0, angle.value[1]);
    rZ = rotate(0, 0, axes.value[2], angle.value[2]);

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
    S.value[0][0] = vectorScaling.value[0];
    S.value[1][1] = vectorScaling.value[1];
    S.value[2][2] = vectorScaling.value[2];

    return (T * R) * S;
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