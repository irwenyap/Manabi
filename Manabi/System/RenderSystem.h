#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H


#include "../Source/System.h"
#include "../Source/Mesh.h"
#include "../Source/Shader.h"
#include "../Components/Camera.hpp"


class RenderSystem : public System {
	enum SHADER_TYPE {
		DEFAULT_SHADER,
		LIGHT_SHADER,
		NONE
	};
public:
	void Initialize();
	void Update(double dt, Camera& camera);
	void Exit();

	//Entity m_camera;
	//Camera m_cameras[] = { 0 }; 
	//std::vector<Camera> m_cameras;
	//Camera &activeCamera;
	std::vector<Shader*> m_shaders;

};


#endif // !RENDER_SYSTEM_H