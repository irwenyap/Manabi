#pragma once

#include "Vector3.h"

struct Light {
	enum LIGHT_TYPE {
		DIRECTIONAL,
		POINT,
		SPOT,
		AREA,
		NONE,
	};
	LIGHT_TYPE type;
	Vector3 color;
};