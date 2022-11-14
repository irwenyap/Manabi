#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "ModelBuilder.hpp"

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model {
public:
	Model(const char* path) {
		LoadModel(path);
	}
	void Render(Shader& shader);

private:
	std::vector<Texture> m_texturesLoaded;
	std::vector<Mesh> m_meshes;
	std::string m_directory;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
};


//class Model {
//public:
//	Model(const char* file_path) {
//		m_filePath = file_path;
//	}
//
//	Mesh* GenerateModel() {
//		std::vector<Vector3> vertices;
//		std::vector<Vector2> texCoords;
//		std::vector<Vector3> normals;
//
//		bool success = ModelBuilder::BuildModel(m_filePath.c_str(), vertices, texCoords, normals);
//		if (!success) {
//			std::cout << "Model Failed to Build" << std::endl;
//			return nullptr;
//		}
//
//		std::vector<GLuint> index_buffer_data;
//		std::vector<Vertex> vertex_buffer_data;
//
//		ModelBuilder::IndexVBO(vertices, texCoords, normals, index_buffer_data, vertex_buffer_data);
//
//		Mesh* mesh = new Mesh();
//		mesh->m_drawMode = Mesh::DRAW_TRIANGLES;
//
//		glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vertexBufferObject);
//		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_indexBufferObject);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
//
//		mesh->indexSize = index_buffer_data.size();
//
//		return mesh;
//	}
//
//	void Render(Mesh* mesh) {
//		mesh->Render();
//	}
//private:
//	std::string m_filePath;
//};



#endif // !MODEL_H

