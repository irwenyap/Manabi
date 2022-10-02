#ifndef RENDERER_H
#define RENDERER_H

#include "../Source/Mesh.h"

struct Renderer {
	Mesh* mesh;
	std::string file_path;
};

#endif // !RENDERER_H