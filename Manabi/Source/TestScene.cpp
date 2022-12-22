//#include <glad/glad.h>

#include "TestScene.h"
//#include "Shader.h"

#include "../Components/Renderer.h"
#include "../Components/Transform.hpp"
#include "../Components/Rigidbody.hpp"
#include "../Components/Collider.hpp";
#include "../Components/CameraController.h";
#include "../Components/PlayerController.hpp";

#include "Application.h"

#include <iostream>

Coordinator g_coordinator;

TestScene::TestScene() {
	cameraIndex = 0;
}

TestScene::~TestScene() {
}

void TestScene::Initialize() {
	g_coordinator.Initialize();

	g_coordinator.RegisterComponent<Transform>();

	g_coordinator.RegisterComponent<Renderer>();

	g_coordinator.RegisterComponent<Rigidbody>();
	g_coordinator.RegisterComponent<Collider>();

	g_coordinator.RegisterComponent<Camera>();
	g_coordinator.RegisterComponent<CameraController>();

	g_coordinator.RegisterComponent<PlayerController>();

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
		signature.set(g_coordinator.GetComponentType<CameraController>());
		g_coordinator.SetSystemSignature<CameraControlSystem>(signature);
	}

	playerControlSystem = g_coordinator.RegisterSystem<PlayerControlSystem>();
	{
		Signature signature;
		signature.set(g_coordinator.GetComponentType<Transform>());
		//signature.set(g_coordinator.GetComponentType<Renderer>());
		signature.set(g_coordinator.GetComponentType<PlayerController>());
		g_coordinator.SetSystemSignature<PlayerControlSystem>(signature);
	}

	//// Register Entities
	// Camera
	auto sceneCamera = g_coordinator.CreateEntity();
	g_coordinator.AddComponent(sceneCamera, Transform{ .position = Vector3(0, 0, -5), .rotation = Vector3(0, 0, 0) });
	g_coordinator.AddComponent(sceneCamera, Camera{ .entity = sceneCamera, .isActive = true, .target = Vector3(0, 0, 1) });
	g_coordinator.AddComponent(sceneCamera, CameraController());

	Camera &sceneCam = g_coordinator.GetComponent<Camera>(sceneCamera);
	sceneCam.projection_matrix.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_cameras.push_back(sceneCam);

	// Player
	{
		// Player Parent
		auto player = g_coordinator.CreateEntity();
		auto playerCamera = g_coordinator.CreateEntity();
		g_coordinator.AddComponent(player, Transform{ .position = Vector3(0, 0, -5), .rotation = Vector3(0, 0, 0), .scale = Vector3(1, 1, 1) });
		g_coordinator.AddComponent(player, PlayerController{ .isGrounded = true, .isJumping = false, .playerSpeed = 10.f, .playerCamera = playerCamera });
		Transform& playerTransform = g_coordinator.GetComponent <Transform>(player);

		// Camera
		g_coordinator.AddComponent(playerCamera, Transform{ .parent = &playerTransform, .localPosition = Vector3(0, 0, 0), .localRotation = Vector3(0, 1, 0), .localScale = Vector3(1, 1, 1) });
		g_coordinator.AddComponent(playerCamera, Camera{ .entity = playerCamera, .isActive = false, .target = Vector3(0, 0, -1), .up = Vector3(0, 1, 0), .right = Vector3(1, 0, 0) });

		Camera& playerCam = g_coordinator.GetComponent<Camera>(playerCamera);

		Transform& test = g_coordinator.GetComponent<Transform>(playerCamera);
		playerCam.projection_matrix.SetToPerspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
		m_cameras.push_back(playerCam);

		// Player Gun
		auto playerGun = g_coordinator.CreateEntity();
		g_coordinator.AddComponent(playerGun, Transform{ .parent = &playerTransform, .localPosition = Vector3(0.4, -0.1, 0.1), .localRotation = Vector3(0, 0, 0), .localScale = Vector3(1, 1, 1) });
		g_coordinator.AddComponent(playerGun, Renderer{ .model = new Model("./Models/Pistol/pistol.obj"), .material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });
	}






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
	//	g_coordinator.AddComponent(floor, Transform{ .position = Vector3(0, 10, 0), .scale = Vector3(1, 1, 1) });
	//	g_coordinator.AddComponent(floor, Renderer{
	//		.model = new Model("./Models/Cube/cube.obj"),
	//		.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

	//	g_coordinator.AddComponent(floor, Rigidbody{
	//		.useGravity = true, .detectCollisions = true,
	//		.position = Vector3(0, 10, 0),
	//		.mass = 10.0f });

	//	g_coordinator.AddComponent(floor, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(1, 1, 1) });
	//}

	{
		Entity mercy = g_coordinator.CreateEntity();
		g_coordinator.AddComponent(mercy, Transform{ .localPosition = Vector3(0, 0, 3), .localScale = Vector3(0.5, 0.5, 0.5) });
		g_coordinator.AddComponent(mercy, Renderer{
			.model = new Model("./Models/Cube/cube.obj"),
			.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

		g_coordinator.AddComponent(mercy, Rigidbody{
			.useGravity = false, .detectCollisions = false,
			.isKinematic = false, .position = Vector3(0, 0, 0),
			.mass = 10.0f });

		g_coordinator.AddComponent(mercy, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(1, 1, 1) });


		Entity floor = g_coordinator.CreateEntity();
		g_coordinator.AddComponent(floor, Transform{ .position = Vector3(0, 5, 0), .rotation = Vector3(0, 0, 0), .scale = Vector3(1, 1, 1)});
		g_coordinator.AddComponent(floor, Renderer{
			.model = new Model("./Models/Cube/cube.obj"),
			.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

		g_coordinator.AddComponent(floor, Rigidbody{
			.useGravity = false, .detectCollisions = false,
			.position = Vector3(0, 5, 0),
			.mass = 10.0f });

		g_coordinator.AddComponent(floor, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(1, 1, 1) });


		Transform& transform1 = g_coordinator.GetComponent<Transform>(mercy);
		Transform& transform2 = g_coordinator.GetComponent<Transform>(floor);

		transform1.parent = &transform2;
	}

	{
		Entity box1 = g_coordinator.CreateEntity();

		g_coordinator.AddComponent(box1, Transform{ .position = Vector3(0, 0, 5), .scale = Vector3(1, 1, 1) });
		g_coordinator.AddComponent(box1, Renderer{
			.model = new Model("./Models/Cube/cube.obj"),
			.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

		g_coordinator.AddComponent(box1, Rigidbody{
			.useGravity = false, .detectCollisions = false,
			.position = Vector3(0, 0, 5), .mass = 10.0f });

		g_coordinator.AddComponent(box1, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(1, 1, 1) });
	}

	{
		Entity floor = g_coordinator.CreateEntity();
		g_coordinator.AddComponent(floor, Transform{ .position = Vector3(0, 0, 0), .rotation = Vector3(0, 0, 0), .scale = Vector3(3, 0.5, 3)});
		g_coordinator.AddComponent(floor, Renderer{
			.model = new Model("./Models/Cube/cube.obj"),
			.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

		g_coordinator.AddComponent(floor, Rigidbody{
			.useGravity = false, .detectCollisions = true,
			.position = Vector3(0, 0, 0),
			.mass = 10.0f });

		g_coordinator.AddComponent(floor, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(3, 0.5, 3) });

		//Entity box = g_coordinator.CreateEntity();
		//g_coordinator.AddComponent(box, Transform{ .position = Vector3(0, 10, 0), .scale = Vector3(0.05, 2, 0.05) });
		//g_coordinator.AddComponent(box, Renderer{
		//	.model = new Model("./Models/Cube/cube.obj"),
		//	.material = new Material(0, Vector3(1.0f, 0.5f, 0.31f), Vector3(1.0f, 0.5f, 0.31f), Vector3(0.5f, 0.5f, 0.5f), 32.0f) });

		//g_coordinator.AddComponent(box, Rigidbody{
		//	.useGravity = false, .detectCollisions = true,
		//	.isKinematic = false, .position = Vector3(0, 10, 0),
		//	.mass = 10.0f });

		//g_coordinator.AddComponent(box, Collider{ .type = Collider::COLLIDER_BOX, .size = Vector3(10, 1, 10) });


		//auto& trans1 = g_coordinator.GetComponent<Transform>(floor);
		//auto& trans2 = g_coordinator.GetComponent<Transform>(box);
		//trans2.parent = &trans1;
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

	playerControlSystem->Initialize();
}

void TestScene::Update(double dt) {

	// Switching of Cameras
	if (Application::IsKeyPressed('Q') && cameraIndex > 0) {
		m_cameras[cameraIndex].get().isActive = false;
		--cameraIndex;
		m_cameras[cameraIndex].get().isActive = true;
	} else if (Application::IsKeyPressed('E') && cameraIndex < m_cameras.size() - 1) {
		m_cameras[cameraIndex].get().isActive = false;
		++cameraIndex;
		m_cameras[cameraIndex].get().isActive = true;
	}

	if (Application::IsKeyPressed('J')) {
		auto& transform = g_coordinator.GetComponent<Transform>(5);
		transform.rotation.y += 80 * dt;
		std::cout << transform.rotation << std::endl;

	}

	//bt += dt;
	//if (Application::IsKeyPressed('L') && bt > 1) {
	//	PhysicsSystem::AddForce(Vector3(10, 20, 0), 1);
	//	bt = 0;
	//}

	transformSystem->Update(dt);
	cameraControlSystem->Update(dt);
	physicsSystem->Update(dt);
	renderSystem->Update(dt, m_cameras[cameraIndex]);

	playerControlSystem->Update(dt);
}

void TestScene::Exit() {
	//for (int i = 0; i < m_cameras.size(); ++i)
	//	free(&m_cameras[i]);
	//m_cameras.clear();

	cameraControlSystem->Exit();
	physicsSystem->Exit();
	renderSystem->Exit();
	transformSystem->Exit();

	playerControlSystem->Exit();

	playerControlSystem.reset();
	cameraControlSystem.reset();
	physicsSystem.reset();
	renderSystem.reset();
	transformSystem.reset();
}
