#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "../Source/System.h"

class PhysicsSystem : public System {
public:
	void Initialize();
	void Update(double dt);
};

#endif // !PHYSICS_SYSTEM_H