#include "RenderSystem.h"

#include "../Source/Coordinator.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Source/stb_image.h"

#include "../Components/Renderer.h"
#include "../Components/Transform.hpp"

#include "MyMath.h"

//Testing
#include "../Source/Application.h"

extern Coordinator g_coordinator;

void RenderSystem::Initialize() {
	shader = new Shader();

	shader->Initialize("Shader/default.vert", "Shader/default.frag");


	m_camera = g_coordinator.CreateEntity();

	//g_coordinator.AddComponent(m_camera, Transform{ .position = Vector3(0, 0, 10), .rotation = Vector3(0, 1, 0), .scale = Vector3(1, 1, 1) });
	g_coordinator.AddComponent(m_camera, Camera{ .position = Vector3(0, 0, 10), .rotation = Vector3(0, 1, 0), .target = Vector3(0, 0, -1) });

	camera = g_coordinator.GetComponent<Camera>(m_camera);
	camera.projection_matrix.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	camera.SetVars();

	for (auto const& entity : m_entities) {
	}

	shader->Use();
	shader->SetMat4("projection", camera.projection_matrix);
}

void RenderSystem::Update(double dt) {

	// Camera
	if (Application::IsKeyPressed('W')) {
		camera.position += 2.0f * camera.target * dt;
	}
	if (Application::IsKeyPressed('A')) {
		camera.position -= 2.0f * (camera.target.Cross(camera.up)).Normalize() * dt;
	}	
	if (Application::IsKeyPressed('S')) {
		camera.position -= 2.0f * camera.target * dt;
	}	
	if (Application::IsKeyPressed('D')) {
		camera.position += 2.0f * (camera.target.Cross(camera.up)).Normalize() * dt;
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
		front.x = cos(Math::DegreeToRadian(camera.yaw));// cos(Math::DegreeToRadian(camera.pitch));
		front.y = sin(Math::DegreeToRadian(camera.pitch));
		front.z = sin(Math::DegreeToRadian(camera.yaw));// * cos(Math::DegreeToRadian(camera.pitch));

		camera.target = front.Normalize();
	}

	{
		camera.direction = (camera.target - camera.position).Normalize();
		camera.right = Vector3(0, 1, 0).Cross(camera.direction).Normalize();
		camera.up = camera.direction.Cross(camera.right).Normalize();
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 view;
	view.SetToIdentity();
	view.SetToLookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.position.x + camera.target.x, camera.position.y + camera.target.y, camera.position.z + camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	shader->SetMat4("view", view);

	for (auto const entity : m_entities) {
		Mtx44 modelTrans, modelRot, model;
		Transform transform = g_coordinator.GetComponent<Transform>(entity);

		//modelTrans.SetToTranslation(transform.position.x, transform.position.y, transform.position.z);
		modelTrans.SetToTranslation(0, 0, 0);
		model = modelTrans;
		shader->SetMat4("model", model);
		g_coordinator.GetComponent<Renderer>(entity).model->Render(*shader);
	}
}

void RenderSystem::Exit() {
	shader->Delete();
}
