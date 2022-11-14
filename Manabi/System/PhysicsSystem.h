#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "../Source/System.h"
#include "../Components/Rigidbody.hpp";
#include "../Components/Collider.hpp";

class PhysicsSystem : public System {
public:
	void Initialize();
	void Update(double dt);
	void Exit();

	const float m_kGRAVITY = -1.8f;

private:
	bool CheckCollision(Collider& c1, Collider& c2);
	bool GetSeparatingPlane(Vector3& vDist, Vector3 plane, Collider c1, Collider c2);
	void CollisionResponse(Rigidbody& r1, Collider& c1, Rigidbody& r2, Collider& c2, float dt);
};

#endif // !PHYSICS_SYSTEM_H