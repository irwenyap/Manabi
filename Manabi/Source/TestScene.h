#pragma once

#include "Scene.h"
#include "Mtx44.h"
#include "MatrixStack.h"
#include <vector>



class TestScene : public Scene {
public:
	TestScene();
	~TestScene();

	virtual void Initialize();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	MS modelStack, viewStack, projectionStack;

	unsigned int m_vertexArrayObject, m_vertexBufferObject, m_elementBufferObject;
	unsigned int texture;
};

