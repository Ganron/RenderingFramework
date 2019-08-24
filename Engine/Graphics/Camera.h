#pragma once
#include"../Math/Vector3.h"

class Matrix4;
namespace Graphics
{
	enum class CameraMovementDirection { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

	class Camera
	{
	public:
		Camera();

		Matrix4 GetViewMatrix() const;
		float GetFieldOfViewAngle() const;

		void MoveCamera(const CameraMovementDirection& direction, float deltaTime);
		void RotateCamera(float xDelta, float yDelta);
		void ZoomCamera(float fovDelta);

	private:
		Vector3 position;
		Vector3 forward;
		Vector3 right;
		float yaw;
		float pitch;
		float fovY; //TODO consider using focal length instead

		void UpdateAxes();
	};

}
