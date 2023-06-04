#include <camera.h>
 
#define PI 3.14159265359f
#define TO_RAD(var) ((var * PI) / 180.f)


Matrix4x4 Camera::LookAt(Vector3 eye, Vector3 center, Vector3 up)
{
	Matrix4x4 view;
    const Vector3 _up = up.Normalize();

    const Vector3 z = (eye - center).Normalize();
    const Vector3 x = Vector3::CrossProduct(_up, z).Normalize();
    const Vector3 y = Vector3::CrossProduct(z, x).Normalize();

    const float r03 = -Vector3::DotProduct(x, eye);
    const float r13 = -Vector3::DotProduct(y, eye);
    const float r23 = -Vector3::DotProduct(z, eye);

    view.value = {
        { x.x, x.y, x.z, r03 },
        { y.x, y.y, y.z, r13 },
        { z.x, z.y, z.z, r23 },
        { 0.0f, 0.0f, 0.0f, 1.0f }
    };
	return view;
}

void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    Vector3 newFront;
    newFront.x = cos(TO_RAD(Yaw)) * cos(TO_RAD(Pitch));
    newFront.y = sin(TO_RAD(Pitch));
    newFront.z = sin(TO_RAD(Yaw)) * cos(TO_RAD(Pitch));
    front = newFront.Normalize();

    // also re-calculate the Right and Up vector
    right = Vector3::CrossProduct(front, worldUP).Normalize();  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = Vector3::CrossProduct(right, front).Normalize();
}

Matrix4x4 Camera::GetViewMatrix()
{
    return LookAt(position, position + front, up);
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        position = position + (front * velocity);
    if (direction == BACKWARD)
        position = position - (front * velocity);
    if (direction == LEFT)
        position = position - (right * velocity);
    if (direction == RIGHT)
        position = position + (right * velocity);
    if (direction == UP)
        position = position + (up * velocity);
    if (direction == DOWN)
        position = position - (up * velocity);
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

// constructor with vectors
Camera::Camera(Vector3 pos, Vector3 up, float yaw, float pitch)
    : front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    position = position;
    worldUP = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// constructor with scalar values
Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    position = Vector3(posX, posY, posZ);
    worldUP = Vector3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}
