#pragma once

#include "Mtx44.h"
#include "Vector3.h"

struct Transform {
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Vector3 localPosition;
	Vector3 localRotation;
	Vector3 localScale;

	Transform* parent;

	Mtx44 localToWorldMatrix;
	Mtx44 worldToLocalMatrix;
};