#include <glad/glad.h>

#include "TestScene.h"
#include "Shader.h"

#include "../Components/Renderer.h"
#include "../Components/Camera.h"
#include "../Components/Transform.hpp"
#include "../Components/Rigidbody.hpp"

#include <iostream>

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
	g_coordinator.RegisterComponent<Rigidbody>();

	renderSystem = g_coordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Transform>());
		signature.set(g_coordinator.GetComponentType<Renderer>());
		g_coordinator.SetSystemSignature<RenderSystem>(signature);
	}

	renderSystem->Initialize();

	physicsSystem = g_coordinator.RegisterSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Transform>());
		signature.set(g_coordinator.GetComponentType<Rigidbody>());
		g_coordinator.SetSystemSignature<PhysicsSystem>(signature);
	}

	physicsSystem->Initialize();

	Entity box = g_coordinator.CreateEntity();

	g_coordinator.AddComponent(box, Transform{ .position = Vector3(0, 10, 0) });
	g_coordinator.AddComponent(box, Renderer{ .model = new Model("./Models/Cube/cube.obj") });
	g_coordinator.AddComponent(box, Rigidbody{ .useGravity = true, .position = Vector3(0, 10, 0), .mass = 10.0f});
}

void TestScene::Update(double dt) {
	renderSystem->Update(dt);
	physicsSystem->Update(dt);
}

void TestScene::Exit() {
	renderSystem->Exit();
}
