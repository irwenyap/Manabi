#ifndef MODEL_BUILDER_HPP
#define MODEL_BUILDER_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <map>

#include <Vector2.h>
#include <Vector3.h>

struct PackedVertex {
	Vector3 position;
	Vector2 texCoord;
	Vector3 normal;
	bool operator<(const PackedVertex that) const {
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};

class ModelBuilder {
public:
	static bool BuildModel(const char* file_path, std::vector<Vector3> &out_vertices, std::vector<Vector2> &out_texCoords, std::vector<Vector3> &out_normals) {
		std::ifstream fileStream(file_path, std::ios::binary);
		if (!fileStream.is_open()) {
			std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
			return false;
		}

		std::vector<unsigned int> vertexIndices, texCoordIndices, normalIndices;
		std::vector<Vector3> temp_vertices;
		std::vector<Vector2> temp_texCoords;
		std::vector<Vector3> temp_normals;

		while (!fileStream.eof()) {
			char lineHeader[256];
			fileStream.getline(lineHeader, 256);
			if (strncmp("v ", lineHeader, 2) == 0) {
				Vector3 vertex;
				sscanf_s((lineHeader + 2), "%f%f%f", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			} else if (strncmp("vt ", lineHeader, 2) == 0) {
				Vector2 texCoord;
				sscanf_s((lineHeader + 2), "%f%f", &texCoord.x, &texCoord.y);
				temp_texCoords.push_back(texCoord);
			} else if (strncmp("vn ", lineHeader, 2) == 0) {
				Vector3 normal;
				sscanf_s((lineHeader + 2), "%f%f%f", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			} else if (strncmp("f ", lineHeader, 2) == 0) {
				unsigned int vertexIndex[4], normalIndex[4], texCoordIndex[4];
				int matches = sscanf_s((lineHeader + 2), "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
					&vertexIndex[0], &texCoordIndex[0], &normalIndex[0],
					&vertexIndex[1], &texCoordIndex[1], &normalIndex[1],
					&vertexIndex[2], &texCoordIndex[2], &normalIndex[2],
					&vertexIndex[3], &texCoordIndex[3], &normalIndex[3]);

				if (matches == 9) {
					// Triangulated Faces
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					texCoordIndices.push_back(texCoordIndex[0]);
					texCoordIndices.push_back(texCoordIndex[1]);
					texCoordIndices.push_back(texCoordIndex[2]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);
				} else if (matches == 12) {
					// Quad Faces
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[1]);
					vertexIndices.push_back(vertexIndex[2]);
					texCoordIndices.push_back(texCoordIndex[0]);
					texCoordIndices.push_back(texCoordIndex[1]);
					texCoordIndices.push_back(texCoordIndex[2]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[1]);
					normalIndices.push_back(normalIndex[2]);

					vertexIndices.push_back(vertexIndex[2]);
					vertexIndices.push_back(vertexIndex[3]);
					vertexIndices.push_back(vertexIndex[0]);
					texCoordIndices.push_back(texCoordIndex[2]);
					texCoordIndices.push_back(texCoordIndex[3]);
					texCoordIndices.push_back(texCoordIndex[0]);
					normalIndices.push_back(normalIndex[2]);
					normalIndices.push_back(normalIndex[3]);
					normalIndices.push_back(normalIndex[0]);
				} else {
					std::cout << "Error line: " << lineHeader << std::endl;
					std::cout << "File cannot be read by parser\n";
					return false;
				}
			}
		}
		fileStream.close();

		for (unsigned int i = 0; i < vertexIndices.size(); ++i) {
			// Get the indices of its attributes
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = texCoordIndices[i];
			unsigned int normalIndex = normalIndices[i];

			// Get the attributes thanks to the index
			Vector3 vertex = temp_vertices[vertexIndex - 1];
			Vector2 uv = temp_texCoords[uvIndex - 1];
			Vector3 normal = temp_normals[normalIndex - 1];

			// Put the attributes in buffers
			out_vertices.push_back(vertex);
			out_texCoords.push_back(uv);
			out_normals.push_back(normal);
		}

		return true;
	}

	static void IndexVBO(
		std::vector<Vector3>& in_vertices,
		std::vector<Vector2>& in_texCoords,
		std::vector<Vector3>& in_normals,
		std::vector<unsigned int>& out_indices,
		std::vector<Vertex>& out_vertices) {

		std::map<PackedVertex, unsigned short> vertexToOutIndex;

		for (unsigned int i = 0; i < in_vertices.size(); ++i) {
			PackedVertex packed = { in_vertices[i], in_texCoords[i], in_normals[i] };

			unsigned short index;
			bool found = CheckSimilarVertexIndex(packed, vertexToOutIndex, index);

			if (found) {
				out_indices.push_back(index);
			} else {
				Vertex v;
				v.position.Set(in_vertices[i].x, in_vertices[i].y, in_vertices[i].z);
				v.texCoord.Set(in_texCoords[i].x, in_texCoords[i].y);
				v.normal.Set(in_normals[i].x, in_normals[i].y, in_normals[i].z);
				out_vertices.push_back(v);

				unsigned int newIndex = (unsigned int)out_vertices.size() - 1;
				out_indices.push_back(newIndex);

				vertexToOutIndex[packed] = newIndex;
			}
		}
	}

	static bool CheckSimilarVertexIndex(
		PackedVertex& packed,
		std::map<PackedVertex, unsigned short>& VertexToOutIndex,
		unsigned short& result) {

		std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
		if (it == VertexToOutIndex.end()) {
			return false;
		} else {
			result = it->second;
			return true;
		}
	}
private:
};

#endif // !MODEL_LOADER_HPP
