#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "MatrixStack.h"

#include "Coordinator.h"

#include "../System/RenderSystem.h"


class TestScene : public Scene {
public:
	TestScene();
	~TestScene();

	virtual void Initialize();
	virtual void Update(double dt);
	virtual void Exit();

private:
	MS modelStack, viewStack, projectionStack;

	std::shared_ptr<RenderSystem> renderSystem;

	Coordinator m_coordinator;
};

