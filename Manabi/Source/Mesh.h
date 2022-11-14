#ifndef MESH_H
#define MESH_H

#define MAX_TEXTURES	8

#include <vector>

#include "Shader.h"
#include "Vertex.h"
#include "Texture.h"

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures);
	~Mesh();

	void Render(Shader& shader);

	std::vector<Vertex> m_vertices;
	std::vector<unsigned> m_indices;
	std::vector<Texture> m_textures;

private:

	void SetupMesh();

	unsigned int m_vertexArrayObject, m_vertexBufferObject, m_elementBufferObject;
};

#endif // !MESH_H