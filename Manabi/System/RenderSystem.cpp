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
	Shader* defaultShad = new Shader();
	Shader* lightShad = new Shader();

	defaultShad->Initialize("Shader/default.vert", "Shader/default.frag");
	lightShad->Initialize("Shader/default.vert", "Shader/light.frag");

	m_shaders.push_back(defaultShad);
	m_shaders.push_back(lightShad);

	m_camera = g_coordinator.CreateEntity();

	g_coordinator.AddComponent(m_camera, Camera{ .position = Vector3(0, 0, 10), .rotation = Vector3(0, 1, 0), .target = Vector3(0, 0, -1) });

	camera = g_coordinator.GetComponent<Camera>(m_camera);
	camera.projection_matrix.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

	auto light = g_coordinator.CreateEntity();
	g_coordinator.AddComponent(light, Transform{ .position = Vector3(10, 10, 10), .scale = Vector3(0.2, 0.2, 0.2) });
	g_coordinator.AddComponent(light, Renderer{ .model = new Model("./Models/Cube/cube.obj"), .material = new Material(1) });
}

void RenderSystem::Update(double dt) {

	// Camera
	if (Application::IsKeyPressed('W')) {
		camera.position += 2.0f * camera.target * dt;
	}
	if (Application::IsKeyPressed('A')) {
		camera.position += 2.0f * camera.right * dt;
	}	
	if (Application::IsKeyPressed('S')) {
		camera.position -= 2.0f * camera.target * dt;
	}	
	if (Application::IsKeyPressed('D')) {
		camera.position -= 2.0f * camera.right * dt;
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

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 view;
	view.SetToIdentity();
	view.SetToLookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.position.x + camera.target.x, camera.position.y + camera.target.y, camera.position.z + camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);

	for (auto const entity : m_entities) {
		Mtx44 modelTrans, modelRot, modelScale, model;
		Transform transform = g_coordinator.GetComponent<Transform>(entity);
		int shaderIndex = g_coordinator.GetComponent<Renderer>(entity).material->shaderIndex;

		m_shaders[shaderIndex]->Use();

		m_shaders[shaderIndex]->SetMat4("projection", camera.projection_matrix);
		m_shaders[shaderIndex]->SetMat4("view", view);

		modelTrans.SetToTranslation(transform.position.x, transform.position.y, transform.position.z);
		modelRot.SetToIdentity();
		modelScale.SetToScale(transform.scale.x, transform.scale.y, transform.scale.z);
		model = modelTrans * modelRot * modelScale;
		m_shaders[shaderIndex]->SetMat4("model", model);
		g_coordinator.GetComponent<Renderer>(entity).model->Render(*m_shaders[shaderIndex]);
		if (shaderIndex == RenderSystem::LIGHT_SHADER) {
			m_shaders[shaderIndex]->SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
			m_shaders[shaderIndex]->SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
		}
	}
}

void RenderSystem::Exit() {
	m_shaders.clear();
}
