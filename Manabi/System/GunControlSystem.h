#pragma once
#include "../Source/System.h"

class GunControlSystem : public System {
public:
	void Initialize();
	void Update(double dt);
	void Exit();
};

