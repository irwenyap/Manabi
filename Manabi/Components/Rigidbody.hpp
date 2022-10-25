#pragma once

#include "Vector3.h";

struct Rigidbody {
	bool useGravity;
	bool detectCollisions;
	bool isKinematic;

	Vector3 position;
	Vector3 velocity;
	float mass;
};