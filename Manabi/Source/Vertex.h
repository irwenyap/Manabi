#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"

struct TexCoord {
	float u, v;
	TexCoord(float u = 0, float v = 0) { Set(u, v); }
	void Set(float u, float v) { this->u = u; this->v = v; }
};

struct Vertex {
	Vector3 position;
	Vector3 normal;
	TexCoord texCoord;
};

#endif // !VERTEX_H