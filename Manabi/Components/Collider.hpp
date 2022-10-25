#pragma once
#include "Vector3.h"
#include "Transform.hpp"

struct Collider {
	enum COLLIDER_TYPE {
		COLLIDER_BOX,
		COLLIDER_SPHERE,
		COLLIDER_CYLINDER,
		NONE,
	};
	COLLIDER_TYPE type;

	Transform* transform;
	Vector3 center;
	Vector3 size;
};