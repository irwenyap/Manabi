//#include <glad/glad.h>

#include "TestScene.h"
//#include "Shader.h"

#include "../Components/Renderer.h"
#include "../Components/Transform.hpp"
#include "../Components/Rigidbody.hpp"
#include "../Components/Collider.hpp";

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
	g_coordinator.RegisterComponent<Collider>();

	// Register System

	transformSystem = g_coordinator.RegisterSystem<TransformSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Transform>());
		g_coordinator.SetSystemSignature<TransformSystem>(signature);
	}

	renderSystem = g_coordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Transform>());
		signature.set(g_coordinator.GetComponentType<Renderer>());
		g_coordinator.SetSystemSignature<RenderSystem>(signature);
	}

	physicsSystem = g_coordinator.RegisterSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Transform>());
		signature.set(g_coordinator.GetComponentType<Rigidbody>());
		signature.set(g_coordinator.GetComponentType<Collider>());
		g_coordinator.SetSystemSignature<PhysicsSystem>(signature);
	}

	cameraControlSystem = g_coordinator.RegisterSystem<CameraControlSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Transform>());
		signature.set(g_coordinator.GetComponentType<Camera>());
		g_coordinator.SetSystemSignature<CameraControlSystem>(signature);
	}

	//// Register Entities
	//Camera
	auto sceneCamera = g_coordinator.CreateEntity();
	g_coordinator.AddComponent(sceneCamera, Transform{ .position = Vector3(0, 0, 10), .rotation = Vector3(0, 1, 0) });
	g_coordinator.AddComponent(sceneCamera, Camera{ .entity = sceneCamera, .isActive = true, .target = Vector3(0, 0, -1) });
	Camera sceneCam = g_coordinator.GetComponent<Camera>(sceneCamera);
	sceneCam.projection_matrix.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_cameras.push_back(sceneCam);
	activeCamera = sceneCam;
	//{
	//	Entity box1 = g_coordinator.CreateEntity();

	//	g_coordinator.AddComponent(box1, Transform{ .position = Vector3(0, 40, 0), .scale = Vector3(1, 1, 1) });
	//	g_coordinator.AddComponent(box1, Renderer{
	//		.model = new Model("./Models/Cube/cube.obj"),
	//		.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

	//	g_coordinator.AddComponent(box1, Rigidbody{
	//		.useGravity = true, .detectCollisions = true,
	//		.position = Vector3(0, 40, 0), .mass = 10.0f });

	//	g_coordinator.AddComponent(box1, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(1, 1, 1) });
	//}

	//{
	//	Entity box1 = g_coordinator.CreateEntity();

	//	g_coordinator.AddComponent(box1, Transform{ .position = Vector3(0, 30, 0), .scale = Vector3(1, 1, 1) });
	//	g_coordinator.AddComponent(box1, Renderer{
	//		.model = new Model("./Models/Cube/cube.obj"),
	//		.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

	//	g_coordinator.AddComponent(box1, Rigidbody{
	//		.useGravity = true, .detectCollisions = true,
	//		.position = Vector3(0, 30, 0), .mass = 10.0f });

	//	g_coordinator.AddComponent(box1, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(1, 1, 1) });
	//}

	//{
	//	Entity box2 = g_coordinator.CreateEntity();

	//	g_coordinator.AddComponent(box2, Transform{ .position = Vector3(0, 20, 0), .scale = Vector3(1, 1, 1) });
	//	g_coordinator.AddComponent(box2, Renderer{
	//		.model = new Model("./Models/Cube/cube.obj"),
	//		.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

	//	g_coordinator.AddComponent(box2, Rigidbody{
	//		.useGravity = true, .detectCollisions = true,
	//		.position = Vector3(0, 20, 0), .mass = 10.0f });

	//	g_coordinator.AddComponent(box2, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(1, 1, 1) });
	//}

	//{
	//	Entity box = g_coordinator.CreateEntity();

	//	g_coordinator.AddComponent(box, Transform{ .position = Vector3(0, 10, 0), .scale = Vector3(1, 1, 1) });
	//	g_coordinator.AddComponent(box, Renderer{
	//		.model = new Model("./Models/Cube/cube.obj"),
	//		.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

	//	g_coordinator.AddComponent(box, Rigidbody{
	//		.useGravity = true, .detectCollisions = true,
	//		.position = Vector3(0, 10, 0), .mass = 10.0f });

	//	g_coordinator.AddComponent(box, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(1, 1, 1) });
	//}

	//{
	//	Entity floor = g_coordinator.CreateEntity();
	//	g_coordinator.AddComponent(floor, Transform{ .position = Vector3(0, 0, 0), .scale = Vector3(1, 1, 1) });
	//	g_coordinator.AddComponent(floor, Renderer{
	//		.model = new Model("./Models/Cube/cube.obj"),
	//		.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

	//	g_coordinator.AddComponent(floor, Rigidbody{
	//		.useGravity = false, .detectCollisions = true,
	//		.isKinematic = true, .position = Vector3(0, 0, 0),
	//		.mass = 10.0f });

	//	g_coordinator.AddComponent(floor, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(1, 1, 1) });
	//}

	{
		Entity floor = g_coordinator.CreateEntity();
		g_coordinator.AddComponent(floor, Transform{ .position = Vector3(0, 0, -5), .scale = Vector3(1, 1, 1) });
		g_coordinator.AddComponent(floor, Renderer{
			.model = new Model("./Models/Pistol/pistol.obj"),
			.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

		g_coordinator.AddComponent(floor, Rigidbody{
			.useGravity = false, .detectCollisions = false,
			.isKinematic = true, .position = Vector3(0, 0, -5),
			.mass = 10.0f });

		g_coordinator.AddComponent(floor, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(1, 1, 1) });
	}

	{
		Entity floor = g_coordinator.CreateEntity();
		g_coordinator.AddComponent(floor, Transform{ .position = Vector3(0, -10, 0), .scale = Vector3(50, 0.5, 50) });
		g_coordinator.AddComponent(floor, Renderer{
			.model = new Model("./Models/Cube/cube.obj"),
			.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

		g_coordinator.AddComponent(floor, Rigidbody{
			.useGravity = false, .detectCollisions = true,
			.isKinematic = true, .position = Vector3(0, -10, 0),
			.mass = 10.0f });

		g_coordinator.AddComponent(floor, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(10, 1, 10) });

		Entity box = g_coordinator.CreateEntity();
		g_coordinator.AddComponent(box, Transform{ .position = Vector3(0, 5, 0), .scale = Vector3(0.1, 0.1, 0.1) });
		g_coordinator.AddComponent(box, Renderer{
			.model = new Model("./Models/Cube/cube.obj"),
			.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

		g_coordinator.AddComponent(box, Rigidbody{
			.useGravity = false, .detectCollisions = true,
			.isKinematic = true, .position = Vector3(0, 0, 0),
			.mass = 10.0f });

		g_coordinator.AddComponent(box, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(10, 1, 10) });

		auto &transform = g_coordinator.GetComponent<Transform>(floor);
		auto &transform2 = g_coordinator.GetComponent<Transform>(box);
		//transform2.parent = &transform;
	}

	auto light = g_coordinator.CreateEntity();
	g_coordinator.AddComponent(light, Transform{ .position = Vector3(4, 4, 4), .scale = Vector3(1, 1, 1) });
	g_coordinator.AddComponent(light, Renderer{
		.model = new Model("./Models/Sphere/sphere.obj"),
		.material = new Material(1, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

	transformSystem->Initialize();
	cameraControlSystem->Initialize();
	physicsSystem->Initialize();
	renderSystem->Initialize();
}

void TestScene::Update(double dt) {

	if (!activeCamera.isActive) {
		for (Camera camera : m_cameras) {
			if (camera.isActive)
				activeCamera = camera;
		}
	}

	transformSystem->Update(dt);
	cameraControlSystem->Update(dt, activeCamera);
	physicsSystem->Update(dt);
	renderSystem->Update(dt, activeCamera);
}

void TestScene::Exit() {
	cameraControlSystem->Exit();
	physicsSystem->Exit();
	renderSystem->Exit();
}
