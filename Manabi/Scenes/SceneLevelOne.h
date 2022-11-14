#pragma once

#include "../Source/Scene.h"
#include "Mtx44.h"
#include "MatrixStack.h"

#include "../Source/Coordinator.h"

#include "../System/RenderSystem.h"
#include "../System/PhysicsSystem.h"

class SceneLevelOne : public Scene {
public:
	SceneLevelOne();
	~SceneLevelOne();

	virtual void Initialize();
	virtual void Update(double dt);
	virtual void Exit();

private:
	std::shared_ptr<RenderSystem> renderSystem;
	std::shared_ptr<PhysicsSystem> physicsSystem;

	//Coordinator m_coordinator;
};

