#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"

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

#endif // !MODEL_H
