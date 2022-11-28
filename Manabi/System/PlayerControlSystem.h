#ifndef PLAYER_CONTROL_SYSTEM_H
#define PLAYER_CONTROL_SYSTEM_H

#include "../Source/System.h"
#include "../Source/Mesh.h"
#include "../Source/Shader.h"
#include "../Components/Camera.hpp"

class PlayerControlSystem : public System {
public:
	void Initialize();
	void Update(double dt);
	void Exit();
};

#endif