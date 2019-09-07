#include"Camera.h"
#include"../Math/Math.h"
#include"../Math/Matrix4.h"
#include<GLFW/glfw3.h>
#include<iostream>

namespace Graphics
{
	const Vector3 WORLD_UP = Vector3(0.0f, 1.0f, 0.0f);
	const float MOVEMENT_SPEED = 2.0f;
	const float MOUSE_SENSITIVITY = 0.002f;

	Camera::Camera() : position(Vector3(0.0f, 0.0f, 0.0f)), forward(Vector3(0.0f, 0.0f, -1.0f)), right(Vector3(1.0f, 0.0f, 0.0f)), yaw(PI), pitch(PI/2.0f), fovY(45.0f)
	{
	}

	Matrix4 Camera::GetViewMatrix() const
	{
		return Matrix4::CreateLookAtForward(position, forward, WORLD_UP);
	}

	Vector3 Camera::GetPosition() const
	{
		return position;
	}

	Vector3 Camera::GetForwardDirection() const
	{
		return forward;
	}

	float Camera::GetFieldOfViewAngle() const
	{
		return DegToRad(fovY);
	}

	void Camera::MoveCamera(const CameraMovementDirection & direction, float deltaTime)
	{
		float speed = deltaTime * MOVEMENT_SPEED;
		switch (direction)
		{
		case CameraMovementDirection::FORWARD: position += forward * speed; break;
		case CameraMovementDirection::BACKWARD: position -= forward * speed; break;
		case CameraMovementDirection::LEFT: position -= right * speed; break;
		case CameraMovementDirection::RIGHT: position += right * speed; break;
		case CameraMovementDirection::UP: position += WORLD_UP * speed; break;
		case CameraMovementDirection::DOWN: position -= WORLD_UP * speed; break;
		}
	}

	void Camera::RotateCamera(float xDelta, float yDelta)
	{
		yaw += xDelta * MOUSE_SENSITIVITY;
		pitch += yDelta * MOUSE_SENSITIVITY;
		
		pitch = Clamp<float>(pitch, DegToRad(25.0f), DegToRad(155.0f)); //TODO play around with clamp values
		
		UpdateAxes();
	}

	void Camera::ZoomCamera(float fovDelta)
	{
		fovY -= fovDelta;
		fovY = Clamp<float>(fovY, 15.0f, 50.0f); // TODO play around with clamp values
	}

	void Camera::UpdateAxes()
	{
		SphericalToCart(Vector3(1.0f, yaw, pitch), forward);
		
		right = Vector3::CrossProduct(forward, WORLD_UP).GetNormalized();
	}
}

