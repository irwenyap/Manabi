#ifndef CAMERA_H
#define CAMERA_H

#include "Mtx44.h"

struct Camera {
	Mtx44 projection_matrix;

	Vector3 position;
	Vector3 rotation;

	Vector3 target;
	Vector3 direction;
	Vector3 up;
	Vector3 right;

	float yaw, pitch;
	float lastX, lastY;

	void SetVars() {
		direction = (target - position).Normalized();
		right = direction.Cross(Vector3(0, 1, 0));
		up = direction.Cross(right);
	}
};

#endif // !CAMERA_H