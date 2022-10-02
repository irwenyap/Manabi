#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"

struct Mesh {
	enum DRAW_MODE {
		DRAW_TRIANGLES,
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST
	};

	Mesh();
	~Mesh();

	void Render();



	DRAW_MODE m_mode;

	std::vector<Vertex> m_vertices;

	unsigned int m_vertexBufferObject, m_elementBufferObject;
	unsigned int m_texture;
	unsigned int m_elementSize;
};

#endif // !MESH_H