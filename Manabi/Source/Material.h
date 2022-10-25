#ifndef MATERIAL_H
#define MATERIAL_H

#include "Shader.h"

struct Material {
	int shaderIndex;

	Material(int index) {
		shaderIndex = index;
	}
};

#endif