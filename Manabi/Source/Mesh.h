#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"
#include "Texture.h"

#include "Shader.h"

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures);
	void Render(Shader& shader);

	std::vector<Vertex> m_vertices;
	std::vector<unsigned> m_indices;
	std::vector<Texture> m_textures;

	//enum DRAW_MODE {
	//	DRAW_TRIANGLES,
	//	DRAW_TRIANGLE_STRIP,
	//	DRAW_LINES,
	//	DRAW_MODE_LAST
	//};

	//Mesh();
	//~Mesh();

	//void Render();



	//DRAW_MODE m_mode;

	//std::vector<Vertex> m_vertices;
private:

	void SetupMesh();

	unsigned int m_vertexArrayObject, m_vertexBufferObject, m_elementBufferObject;
	//unsigned int m_texture;
	//unsigned int m_elementSize;
};

#endif // !MESH_H