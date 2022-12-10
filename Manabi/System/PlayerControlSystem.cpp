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

			//if (Application::IsKeyPressed('W')) {
			//	transform.position += 4 * camera.target * dt;
			//}

			//Transform& transform = g_coordinator.GetComponent<Transform>(camera.entity);

			if (Application::IsKeyPressed('W')) {
				transform.position += 2.0f * camera.target * dt;
			}
			if (Application::IsKeyPressed('A')) {
				transform.position += 2.0f * camera.right * dt;
			}
			if (Application::IsKeyPressed('S')) {
				transform.position -= 2.0f * camera.target * dt;
			}
			if (Application::IsKeyPressed('D')) {
				transform.position -= 2.0f * camera.right * dt;
			}

			{
				float xPos = static_cast<float>(Application::mouse_current_x);
				float yPos = static_cast<float>(Application::mouse_current_y);

				float xOffSet = xPos - camera.lastX;
				float yOffSet = camera.lastY - yPos;
				camera.lastX = xPos;
				camera.lastY = yPos;

				float sensitivity = 0.1f;
				xOffSet *= sensitivity;
				yOffSet *= sensitivity;

				camera.yaw += xOffSet;
				camera.pitch += yOffSet;


				if (camera.pitch > 89.0f)
					camera.pitch = 89.0f;
				if (camera.pitch < -89.0f)
					camera.pitch = -89.0f;

				Vector3 front;
				front.x = cos(Math::DegreeToRadian(camera.yaw)) * cos(Math::DegreeToRadian(camera.pitch));
				front.y = sin(Math::DegreeToRadian(camera.pitch));
				front.z = sin(Math::DegreeToRadian(camera.yaw)) * cos(Math::DegreeToRadian(camera.pitch));

				camera.target = front.Normalize();

				camera.right = Vector3(0, 1, 0).Cross(camera.target).Normalize();
				camera.up = camera.target.Cross(camera.right).Normalize();
			}
		}
	}

}

void PlayerControlSystem::Exit() {
}
