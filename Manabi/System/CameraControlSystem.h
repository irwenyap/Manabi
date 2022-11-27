#pragma once

#include "../Source/System.h"

#include "../Components/Camera.hpp"

class CameraControlSystem : public System {
public:
	void Initialize();
	void Update(double dt, Camera& camera);
	void Exit();
};

