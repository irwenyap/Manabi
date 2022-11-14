#include <glad/glad.h>

#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned> indices, std::vector<Texture> textures) {
	m_vertices = vertices;
	m_indices = indices;
	m_textures = textures;

    SetupMesh();
}

Mesh::~Mesh() {
    //glDeleteVertexArrays(1, &m_vertexArrayObject);
    //glDeleteBuffers(1, &m_vertexBufferObject);
    //glDeleteBuffers(1, &m_elementBufferObject);
}


void Mesh::Render(Shader& shader) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < m_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = m_textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
    }

    // Draw mesh
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Setting back to default
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetupMesh() {
    glGenVertexArrays(1, &m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBufferObject);
    glGenBuffers(1, &m_elementBufferObject);

    glBindVertexArray(m_vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int),
        &m_indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);
}


