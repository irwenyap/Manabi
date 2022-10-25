#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H


#include "../Source/System.h"
#include "../Source/Mesh.h"
#include "../Source/Shader.h"
#include "../Components/Camera.h"


class RenderSystem : public System {
	enum SHADER_TYPE {
		DEFAULT_SHADER,
		LIGHT_SHADER,
		NONE
	};
public:
	void Initialize();
	void Update(double dt);
	void Exit();

	Entity m_camera;
	//Test
	Camera camera;

	std::vector<Shader*> m_shaders;
};


#endif // !RENDER_SYSTEM_H