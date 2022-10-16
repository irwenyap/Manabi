#ifndef VERTEX_H
#define VERTEX_H

#include "Vector2.h"
#include "Vector3.h"

struct Vertex {
	Vector3 position;
	Vector3 normal;
	Vector2 texCoord;
	Vector3 tangent;
	Vector3 bitangent;
};

#endif // !VERTEX_H