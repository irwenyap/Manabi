#include "PhysicsSystem.h"

#include "../Source/Coordinator.h"

#include "../Components/Rigidbody.hpp";
#include "../Components/Transform.hpp";

extern Coordinator g_coordinator;

void PhysicsSystem::Initialize() {
}

void PhysicsSystem::Update(double dt) {
	for (auto const& entity : m_entities) {
		Rigidbody rb = g_coordinator.GetComponent<Rigidbody>(entity);
		//if (rb.useGravity) {
		//	rb.position.y += m_kGRAVITY * dt;
		//}

		Transform transform = g_coordinator.GetComponent<Transform>(entity);
		transform.position = rb.position;
	}
}

void PhysicsSystem::Exit() {
}
