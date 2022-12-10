#include "CameraControlSystem.h"

#include "../Source/Coordinator.h"

#include "../Components/Transform.hpp";
#include "../Components/Camera.hpp";

#include "../Source/Application.h"

extern Coordinator g_coordinator;

void CameraControlSystem::Initialize() {

}

void CameraControlSystem::Update(double dt) {
	for (auto& entity : m_entities) {

		Camera &camera = g_coordinator.GetComponent<Camera>(entity);
		if (!camera.isActive)
			continue;

		Transform &transform = g_coordinator.GetComponent<Transform>(camera.entity);

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

			//camera.yaw += xOffSet;
			//camera.pitch += yOffSet;
			transform.rotation.y += xOffSet;
			transform.rotation.x += yOffSet;

			if (transform.rotation.x > 89.0f)
				transform.rotation.x = 89.0f;
			if (transform.rotation.x < -89.0f)
				transform.rotation.x = -89.0f;

			Vector3 forward;
			forward.x = cos(Math::DegreeToRadian(transform.rotation.y)) * cos(Math::DegreeToRadian(transform.rotation.x));
			forward.y = sin(Math::DegreeToRadian(transform.rotation.x));
			forward.z = sin(Math::DegreeToRadian(transform.rotation.y)) * cos(Math::DegreeToRadian(transform.rotation.x));


			camera.target = forward.Normalize();

			camera.right = Vector3(0, 1, 0).Cross(camera.target).Normalize();
			camera.up = camera.target.Cross(camera.right).Normalize();
		}
	}
}

void CameraControlSystem::Exit() {
}
