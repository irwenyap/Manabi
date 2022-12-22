#include "GunControlSystem.h"
#include "../Source/Coordinator.h"

#include "../Components/Gun.h"
#include "../Components/Bullet.h"
#include "../Components/Renderer.h"
#include "../Components/Rigidbody.hpp"
#include "../Components/Collider.hpp"

extern Coordinator g_coordinator;


void GunControlSystem::Initialize() {
}

void GunControlSystem::Update(double dt) {
	for (auto& entity : m_entities) {
		Gun& gun = g_coordinator.GetComponent<Gun>(entity);
		Transform& transform = g_coordinator.GetComponent<Transform>(entity);
		if (gun.isEquipped) {

			if (gun.fireRateTimer <= gun.fireRate) {
				gun.fireRateTimer += dt;
			} else if (gun.shoot) {
				Entity bullet = g_coordinator.CreateEntity();
				g_coordinator.AddComponent(bullet, Bullet());
				g_coordinator.AddComponent(bullet, Transform());
				g_coordinator.AddComponent(bullet, Renderer{ .model = new Model("./Models/Sphere/sphere.obj"), .material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });
				g_coordinator.AddComponent(bullet, Rigidbody{
					.useGravity = false, .detectCollisions = true,
					.position = transform.position });
				g_coordinator.AddComponent(bullet, Collider{ .type = Collider::COLLIDER_BOX });
			}
		}
	}
}

void GunControlSystem::Exit() {
}
