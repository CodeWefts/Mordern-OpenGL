#include <mat4.h>
#include <vec3.h>
#include <glad/glad.h>

// Default camera values
const float YAW =            -90.0f;
const float PITCH =          0.0f;
const float SPEED =          2.5f;
const float SENSITIVITY =    0.1f;
const float ZOOM =           45.0f;

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
private:
	void updateCameraVectors();
public:

	Vector3 position;
	Vector3 front;
	Vector3 up;
	Vector3 right;
	Vector3 worldUP;

	// euler Angles
	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Matrix4x4 LookAt(Vector3 eye, Vector3 center, Vector3 up);
	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	Matrix4x4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ProcessMouseScroll(float yoffset);


	Camera(Vector3 pos = Vector3(0.0f, 0.0f, 0.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
};

