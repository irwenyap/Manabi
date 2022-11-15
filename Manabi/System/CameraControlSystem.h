#pragma once

#include "../Source/System.h"

#include "../Components/Camera.hpp"

class CameraControlSystem : public System {
public:
	void Initialize();
	void Update(double dt);
	void Exit();

	//std::vector<Transform> m_cameras;
	//std::vector<Camera> m_cameras;
};

