#include "PhysicsSystem.h"

#include "../Source/Coordinator.h"

#include "../Components/Transform.hpp";

extern Coordinator g_coordinator;

void PhysicsSystem::Initialize() {
	for (auto const& entity : m_entities) {
		Collider& col = g_coordinator.GetComponent<Collider>(entity);
		col.transform = &g_coordinator.GetComponent<Transform>(entity);
	}
}

void PhysicsSystem::Update(double dt) {
	int x = 1;
	for (std::set<Entity>::iterator it = m_entities.begin(); it != m_entities.end(); ++it) {
		Rigidbody& rb1 = g_coordinator.GetComponent<Rigidbody>(*it);
		if (rb1.useGravity) {
			rb1.velocity.y += m_kGRAVITY * dt;
		}

		if (rb1.detectCollisions) {
			std::set<Entity>::iterator it2 = it;
			for (int y = x; y < m_entities.size(); ++y) {
				std::advance(it2, 1);
				Rigidbody& rb2 = g_coordinator.GetComponent<Rigidbody>(*it2);
				if (rb2.detectCollisions) {
					Collider& c1 = g_coordinator.GetComponent<Collider>(*it);
					Collider& c2 = g_coordinator.GetComponent<Collider>(*it2);
					if (CheckCollision(c1, c2)) {
						CollisionResponse(rb1, c1, rb2, c2, dt);
					}
				}
			}
		}

		// Velocity
		rb1.position += rb1.velocity * dt;
		Transform& transform = g_coordinator.GetComponent<Transform>(*it);
		transform.position = rb1.position;
		
		++x;
	}
}

void PhysicsSystem::Exit() {
	//for (auto const& entity : m_entities) {
	//	Collider& col = g_coordinator.GetComponent<Collider>(entity);
	//	if (col.transform)
	//		delete(col.transform);
	//}
}

bool PhysicsSystem::CheckCollision(Collider& c1, Collider& c2) {
	Vector3 vDist = c1.transform->position - c2.transform->position;
	return !(GetSeparatingPlane(vDist, Vector3(1, 0, 0), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 1, 0), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 0, 1), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(1, 0, 0), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 1, 0), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 0, 1), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(1, 0, 0).Cross(Vector3(1, 0, 0)), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(1, 0, 0).Cross(Vector3(0, 1, 0)), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(1, 0, 0).Cross(Vector3(0, 0, 1)), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 1, 0).Cross(Vector3(1, 0, 0)), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 1, 0).Cross(Vector3(0, 1, 0)), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 1, 0).Cross(Vector3(0, 0, 1)), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 0, 1).Cross(Vector3(1, 0, 0)), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 0, 1).Cross(Vector3(0, 1, 0)), c1, c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 0, 1).Cross(Vector3(0, 0, 1)), c1, c2));
}

bool PhysicsSystem::GetSeparatingPlane(Vector3& vDist, Vector3 plane, Collider c1, Collider c2) {
	return (fabs(vDist.Dot(plane)) >
		(fabs((Vector3(1, 0, 0) * (c1.size.x / 2)).Dot(plane)) +
			fabs((Vector3(0, 1, 0) * (c1.size.y / 2)).Dot(plane)) +
			fabs((Vector3(0, 0, 1) * (c1.size.z / 2)).Dot(plane)) +
			fabs((Vector3(1, 0, 0) * (c2.size.x / 2)).Dot(plane)) +
			fabs((Vector3(0, 1, 0) * (c2.size.y / 2)).Dot(plane)) +
			fabs((Vector3(0, 0, 1) * (c2.size.z / 2)).Dot(plane))));
}

void PhysicsSystem::CollisionResponse(Rigidbody& r1, Collider& c1, Rigidbody& r2, Collider& c2, float dt) {
	switch (c1.type) {
	default:
		break;
	case Collider::COLLIDER_BOX:
		switch (c2.type) {
			case Collider::COLLIDER_BOX:
				r1.velocity.SetZero();
				Vector3 normal = r1.position - r2.position;
				float dist = 1 - (r1.position.y - r2.position.y);
				r1.position += normal * dist;
		}
		break;
	}


	//if (r2.isKinematic) {
	//	r1.velocity.SetZero();
	//}
	//else {

	//}
}
