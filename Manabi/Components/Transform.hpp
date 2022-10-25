#pragma once

#include "Vector3.h"

struct Transform {
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Vector3 localPosition;
	Vector3 localRotation;
	Vector3 localScale;

	Transform* parent;
};