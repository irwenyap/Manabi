#pragma once

#include "../Source/System.h"

class RenderSystem : public System {
public:
	void Initialize();
	void Update(double dt);

private:
	unsigned int m_vertexArrayObject, m_vertexBufferObject, m_elementBufferObject;
	unsigned int texture;
};

