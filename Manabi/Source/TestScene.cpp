#include "TestScene.h"
#include <glad/glad.h>
#include "Shader.h"
#include "../Components/Renderer.h"
#include "../Components/Camera.h"
#include "../Components/Transform.hpp"

Coordinator g_coordinator;

TestScene::TestScene() {
}

TestScene::~TestScene() {
}

void TestScene::Initialize() {

	g_coordinator.Initialize();

	g_coordinator.RegisterComponent<Transform>();
	g_coordinator.RegisterComponent<Renderer>();
	g_coordinator.RegisterComponent<Camera>();

	renderSystem = g_coordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Renderer>());
		g_coordinator.SetSystemSignature<RenderSystem>(signature);
	}

	renderSystem->Initialize();

	std::vector<Entity> entities(1);

	for (auto& entity : entities) {
		entity = g_coordinator.CreateEntity();
		g_coordinator.AddComponent(entity, Renderer{new Mesh, "../Models/cube.obj" });
	}
}

void TestScene::Update(double dt) {
	renderSystem->Update(dt);
}

void TestScene::Exit() {
	//glDeleteVertexArrays(1, &m_vertexArrayObject);
	//glDeleteBuffers(1, &m_vertexBufferObject);
	//glDeleteBuffers(1, &m_elementBufferObject);

	//shader.Delete();
}
