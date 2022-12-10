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
	lightShad->Initialize("Shader/light.vert", "Shader/light.frag");

	m_shaders.push_back(defaultShad);
	m_shaders.push_back(lightShad);
}

void RenderSystem::Update(double dt, Camera& camera) {
	Transform &camTransform = g_coordinator.GetComponent<Transform>(camera.entity);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Mtx44 view;
	view.SetToIdentity();
	// PROBLEM
	view.SetToLookAt(camTransform.position.x, camTransform.position.y, camTransform.position.z,
		camTransform.position.x + camera.target.x, camTransform.position.y + camera.target.y, camTransform.position.z + camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);

	for (auto const& entity : m_entities) {
		Transform &transform = g_coordinator.GetComponent<Transform>(entity);
		Material *material = g_coordinator.GetComponent<Renderer>(entity).material;
		int shaderIndex = material->m_shaderIndex;

		m_shaders[shaderIndex]->Use();

		m_shaders[shaderIndex]->SetMat4("projection", camera.projection_matrix);
		m_shaders[shaderIndex]->SetMat4("view", view);

		m_shaders[shaderIndex]->SetMat4("model", transform.localToWorldMatrix);
		g_coordinator.GetComponent<Renderer>(entity).model->Render(*m_shaders[shaderIndex]);
		if (shaderIndex == RenderSystem::DEFAULT_SHADER) {
			Vector3 lightpos = Vector3(4, 4, 4);
			m_shaders[shaderIndex]->SetVec3("viewPos", camTransform.position);

			m_shaders[shaderIndex]->SetInt("material.diffuse", 0);
			m_shaders[shaderIndex]->SetVec3("material.specular", material->m_specular);
			m_shaders[shaderIndex]->SetFloat("material.shininess", material->m_shininess);

			m_shaders[shaderIndex]->SetVec3("light.position", lightpos);
			m_shaders[shaderIndex]->SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
			m_shaders[shaderIndex]->SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
			m_shaders[shaderIndex]->SetVec3("light.specular", 1.0f, 1.0f, 1.0f);
		}
	}
}

void RenderSystem::Exit() {
	
	for (int i = 0; i < m_shaders.size(); ++i)
		delete(m_shaders[i]);

	m_shaders.clear();

	for (auto const& entity : m_entities) {
		Renderer renderer = g_coordinator.GetComponent<Renderer>(entity);
		delete(renderer.material);
		delete(renderer.model);
	}
}
