#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "MatrixStack.h"

#include "Coordinator.h"

#include "../System/RenderSystem.h"
#include "../System/PhysicsSystem.h"
#include "../System/TransformSystem.h"
#include "../System/CameraControlSystem.h"
#include "../System/PlayerControlSystem.h"


class TestScene : public Scene {
public:
	TestScene();
	~TestScene();

	virtual void Initialize();
	virtual void Update(double dt);
	virtual void Exit();

private:
	std::shared_ptr<RenderSystem> renderSystem;
	std::shared_ptr<TransformSystem> transformSystem;
	std::shared_ptr<PhysicsSystem> physicsSystem;
	std::shared_ptr<CameraControlSystem> cameraControlSystem;
	std::shared_ptr<PlayerControlSystem> playerControlSystemSystem;

	Coordinator m_coordinator;
};

