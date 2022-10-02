#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H


#include "../Source/System.h"
#include "../Source/Mesh.h"
#include "../Source/Shader.h"
#include "../Components/Camera.h"

class RenderSystem : public System {
public:
	void Initialize();
	void Update(double dt);

	void RenderMesh(Mesh* mesh);

	Entity m_camera;
	//Test
	Camera camera;
	Shader shader;

	unsigned m_vertexArrayObject;



	unsigned int VBO, VAO, texture;
};


#endif // !RENDER_SYSTEM_H