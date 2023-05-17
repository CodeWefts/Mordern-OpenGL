#include <mat4.h>
#include <vec4.h>

#include <assert.h>

using namespace std;


Matrix4x4::Matrix4x4()
{
    for (int i = 0; i < 4; i++)
        this->value.push_back(vector<float>(4, 0.f));
}

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



Matrix4x4 Matrix4x4::rotationMatrix3X3(float_t x, float_t y, float_t z, float_t angle)
{
    Matrix4x4 newMatrix;

    newMatrix.value =
    {
        {x * x * (1 - cosf(angle)) + cosf(angle), y * x * (1 - cosf(angle)) - z * sinf(angle), z * x * (1 - cosf(angle)) + y * sinf(angle)} ,
        {x * y * (1 - cosf(angle)) + z * sinf(angle), y * y * (1 - cosf(angle)) + cosf(angle), z * y * (1 - cosf(angle)) - x * sinf(angle)} ,
        {x * z * (1 - cosf(angle)) - y * sinf(angle), y * z * (1 - cosf(angle)) - x * sinf(angle), z * z * (1 - cosf(angle)) + cosf(angle)}
    };

    return newMatrix;
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
    rX = rotationMatrix3X3(axes.value[0], 0, 0, angle.value[0]);
    rY = rotationMatrix3X3(0, axes.value[1], 0, angle.value[1]);
    rZ = rotationMatrix3X3(0, 0, axes.value[2], angle.value[2]);

    rotation = rZ * (rX * rY);

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