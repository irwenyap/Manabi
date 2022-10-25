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
	//for (auto const& entity : m_entities) {
	//	Rigidbody& rb1 = g_coordinator.GetComponent<Rigidbody>(entity);
	//	if (rb1.useGravity) {
	//		rb1.position.y += m_kGRAVITY * dt;
	//	}

	//	if (rb1.detectCollisions) {
	//		Collider& collider1 = g_coordinator.GetComponent<Collider>(entity);
	//		
	//		for (auto const& entity2 : m_entities) {


	//		}

	//	}






	//	Transform& transform = g_coordinator.GetComponent<Transform>(entity);
	//	transform.position = rb1.position;
	//}
	int x = 0;
	for (std::set<Entity>::iterator it = m_entities.begin(); it != m_entities.end(); ++it) {
		Rigidbody& rb1 = g_coordinator.GetComponent<Rigidbody>(*it);
		if (rb1.useGravity) {
			rb1.velocity.y += m_kGRAVITY * dt;
		}

		if (rb1.detectCollisions) {
			std::set<Entity>::iterator it2 = m_entities.begin();
			for (int y = 1 + x; y != m_entities.size(); ++y) {
				std::advance(it2, y);
				Rigidbody& rb2 = g_coordinator.GetComponent<Rigidbody>(*it2);
				if (rb2.detectCollisions) {
					Collider& c1 = g_coordinator.GetComponent<Collider>(*it);
					Collider& c2 = g_coordinator.GetComponent<Collider>(*it2);
					if (CheckCollision(c1, c2)) {
						CollisionResponse(rb1, rb2, dt);
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
}

bool PhysicsSystem::CheckCollision(Collider& c1, Collider& c2) {
	//std::cout << c1.transform->position << " : " << c2.transform->position << std::endl;

	Vector3 vDist = c1.transform->position - c2.transform->position;
	return !(GetSeparatingPlane(vDist, Vector3(1, 0, 0), c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 1, 0), c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 0, 1), c2) ||
		GetSeparatingPlane(vDist, Vector3(1, 0, 0), c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 1, 0), c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 0, 1), c2) ||
		GetSeparatingPlane(vDist, Vector3(1, 0, 0).Cross(Vector3(1, 0, 0)), c2) ||
		GetSeparatingPlane(vDist, Vector3(1, 0, 0).Cross(Vector3(0, 1, 0)), c2) ||
		GetSeparatingPlane(vDist, Vector3(1, 0, 0).Cross(Vector3(0, 0, 1)), c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 1, 0).Cross(Vector3(1, 0, 0)), c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 1, 0).Cross(Vector3(0, 1, 0)), c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 1, 0).Cross(Vector3(0, 0, 1)), c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 0, 1).Cross(Vector3(1, 0, 0)), c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 0, 1).Cross(Vector3(0, 1, 0)), c2) ||
		GetSeparatingPlane(vDist, Vector3(0, 0, 1).Cross(Vector3(0, 0, 1)), c2));
}

bool PhysicsSystem::GetSeparatingPlane(Vector3& vDist, Vector3 plane, Collider otherBox) {
	return (fabs(vDist.Dot(plane)) >
		(fabs((Vector3(1, 0, 0) * 0.5).Dot(plane)) +
			fabs((Vector3(0, 1, 0) * 0.5).Dot(plane)) +
			fabs((Vector3(0, 0, 1) * 0.5).Dot(plane)) +
			fabs((Vector3(1, 0, 0) * 0.5).Dot(plane)) +
			fabs((Vector3(0, 1, 0) * 0.5).Dot(plane)) +
			fabs((Vector3(0, 0, 1) * 0.5).Dot(plane))));
}

void PhysicsSystem::CollisionResponse(Rigidbody& r1, Rigidbody& r2, float dt) {
	if (r2.isKinematic) {
		r1.velocity.SetZero();
	}
	else {

	}
}
