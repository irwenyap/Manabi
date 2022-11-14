#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "MatrixStack.h"

#include "Coordinator.h"

#include "../System/RenderSystem.h"
#include "../System/PhysicsSystem.h"


class TestScene : public Scene {
public:
	TestScene();
	~TestScene();

	virtual void Initialize();
	virtual void Update(double dt);
	virtual void Exit();

private:
	std::shared_ptr<RenderSystem> renderSystem;
	std::shared_ptr<PhysicsSystem> physicsSystem;

	Coordinator m_coordinator;
};

