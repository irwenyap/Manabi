#include "PlayerControlSystem.h"

#include "../Source/Coordinator.h"

#include "../Components/Transform.hpp"
#include "../Components/PlayerController.hpp"

#include "../Source/Application.h"

extern Coordinator g_coordinator;

void PlayerControlSystem::Initialize() {
}

void PlayerControlSystem::Update(double dt) {
	for (auto& entity : m_entities) {
		auto& cameraEntity = g_coordinator.GetComponent<PlayerController>(entity).playerCamera;
		auto& camera = g_coordinator.GetComponent<Camera>(cameraEntity);
		if (camera.isActive) {
			auto& transform = g_coordinator.GetComponent<Transform>(entity);

			if (Application::IsKeyPressed('W')) {
				transform.position += 4 * camera.target * dt;
			}
		}
	}

}

void PlayerControlSystem::Exit() {
}
