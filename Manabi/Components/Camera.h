#ifndef CAMERA_H
#define CAMERA_H

#include "Mtx44.h"

struct Camera {
	Mtx44 projection_matrix;

	Vector3 position;
	Vector3 rotation;

	Vector3 target;
	Vector3 up;
	Vector3 right;

	float yaw, pitch;
	float lastX, lastY;
};

#endif // !CAMERA_H