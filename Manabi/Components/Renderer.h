#ifndef RENDERER_H
#define RENDERER_H

#include "../Source/Model.h"
#include "../Source/Material.h"

struct Renderer {
	Model *model;
	Material *material;
};

#endif // !RENDERER_H