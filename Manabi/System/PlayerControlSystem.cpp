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
		Entity cameraEntity = g_coordinator.GetComponent<PlayerController>(entity).playerCamera;
		Camera& camera = g_coordinator.GetComponent<Camera>(cameraEntity);
		if (camera.isActive) {
			Transform& transform = g_coordinator.GetComponent<Transform>(entity);

			float dirX = cos(Math::DegreeToRadian(camera.rotation.y));
			float dirZ = sin(Math::DegreeToRadian(camera.rotation.y));

			Vector3 dir = Vector3(dirX, 0, dirZ);

			if (Application::IsKeyPressed('W')) {
				transform.position += 2.0f * dir * dt;
			}
			if (Application::IsKeyPressed('A')) {
				transform.position += 2.0f * camera.right * dt;
			}
			if (Application::IsKeyPressed('S')) {
				transform.position -= 2.0f * dir * dt;
			}
			if (Application::IsKeyPressed('D')) {
				transform.position -= 2.0f * camera.right * dt;
			}

			if (Application::IsKeyPressed('G')) {
				//auto& transform = g_coordinator.GetComponent<Transform>(5);
				transform.rotation.y += 80 * dt;
			}

			{
				float xPos = static_cast<float>(Application::mouse_current_x);
				float yPos = static_cast<float>(Application::mouse_current_y);

				float xCamOffSet = xPos - camera.lastX;
				float yCamOffSet = camera.lastY - yPos;
				float xOffSet = camera.lastX - xPos;
				float yOffSet = yPos - camera.lastY;

				camera.lastX = xPos;
				camera.lastY = yPos;

				float sensitivity = 0.1f;
				xOffSet *= sensitivity;
				yOffSet *= sensitivity;
				xCamOffSet *= sensitivity;
				yCamOffSet *= sensitivity;

				transform.rotation.y += xOffSet;
				transform.rotation.x += yOffSet;

				camera.rotation.y += xCamOffSet;
				camera.rotation.x += yCamOffSet;

				if (transform.rotation.x > 89.0f) {
					transform.rotation.x = 89.0f;
					camera.rotation.x = 89.0f;
				}
				if (transform.rotation.x < -89.0f) {
					transform.rotation.x = -89.0f;
					camera.rotation.x = -89.0f;
				}

				Vector3 forward;
				forward.x = dirX * cos(Math::DegreeToRadian(camera.rotation.x));
				forward.y = sin(Math::DegreeToRadian(camera.rotation.x));
				forward.z = dirZ * cos(Math::DegreeToRadian(camera.rotation.x));

				camera.target = forward.Normalize();

				camera.right = Vector3(0, 1, 0).Cross(camera.target).Normalize();
				camera.up = camera.target.Cross(camera.right).Normalize();
			}
		}
	}
}

void PlayerControlSystem::Exit() {
}
