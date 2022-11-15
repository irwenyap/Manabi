#include "SceneLevelOne.h"

#include "../Components/Renderer.h"
#include "../Components/Camera.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Rigidbody.hpp"
#include "../Components/Collider.hpp";

//Coordinator g_coordinator;

SceneLevelOne::SceneLevelOne() {
}

SceneLevelOne::~SceneLevelOne() {
}

void SceneLevelOne::Initialize() {
	//g_coordinator.Initialize();

	//g_coordinator.RegisterComponent<Transform>();
	//g_coordinator.RegisterComponent<Renderer>();
	//g_coordinator.RegisterComponent<Camera>();
	//g_coordinator.RegisterComponent<Rigidbody>();
	//g_coordinator.RegisterComponent<Collider>();

	//// Register System

	//renderSystem = g_coordinator.RegisterSystem<RenderSystem>();
	//{
	//	Signature signature;
	//	signature.set(g_coordinator.GetComponentType<Transform>());
	//	signature.set(g_coordinator.GetComponentType<Renderer>());
	//	g_coordinator.SetSystemSignature<RenderSystem>(signature);
	//}


	//physicsSystem = g_coordinator.RegisterSystem<PhysicsSystem>();
	//{
	//	Signature signature;
	//	signature.set(g_coordinator.GetComponentType<Transform>());
	//	signature.set(g_coordinator.GetComponentType<Rigidbody>());
	//	signature.set(g_coordinator.GetComponentType<Collider>());
	//	g_coordinator.SetSystemSignature<PhysicsSystem>(signature);
	//}


}

void SceneLevelOne::Update(double dt) {
}

void SceneLevelOne::Exit() {
}
