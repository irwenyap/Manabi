#ifndef TRANSFORM_SYSTEM_H
#define TRANSFORM_SYSTEM_H

#include "../Source/System.h"

class TransformSystem : public System {
public:
	void Initialize();
	void Update(double dt);
	void Exit();

	void ConvertWorldToLocalMatrix();
};

#endif // !TRANSFORM_SYSTEM_H