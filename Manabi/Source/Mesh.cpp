#include <glad/glad.h>

#include "Mesh.h"

Mesh::Mesh() {
	glGenBuffers(1, &m_vertexBufferObject);
	glGenBuffers(1, &m_elementBufferObject);
}

Mesh::~Mesh() {
}

void Mesh::Render() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	//if (textureID > 0) {
	//	glEnableVertexAttribArray(3);
	//	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	//}


	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferObject);

	if (m_mode == DRAW_LINES)
		glDrawElements(GL_LINES, m_elementSize, GL_UNSIGNED_INT, 0);
	else if (m_mode == DRAW_TRIANGLE_STRIP)
		glDrawElements(GL_TRIANGLE_STRIP, m_elementSize, GL_UNSIGNED_INT, 0);
	else
		glDrawElements(GL_TRIANGLES, m_elementSize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//if (textureID > 0) {
	//	glDisableVertexAttribArray(3);
	//}
}
