#include "CameraControlSystem.h"

#include "../Source/Coordinator.h"

#include "../Components/Transform.hpp";
#include "../Components/Camera.hpp";

extern Coordinator g_coordinator;

void CameraControlSystem::Initialize() {
	Entity sceneCamera = g_coordinator.CreateEntity();
	g_coordinator.AddComponent(sceneCamera,
		Transform{ .position = Vector3(0, 0, -10), .rotation = Vector3(0, 1, 0), .scale = Vector3(1, 1, 1) });
	g_coordinator.AddComponent(sceneCamera,
		Camera{ });


}

void CameraControlSystem::Update(double dt) {
}

void CameraControlSystem::Exit() {
}
