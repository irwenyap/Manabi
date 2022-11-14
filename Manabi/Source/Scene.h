#ifndef SCENE_H
#define SCENE_H

//Coordinator g_coordinator;

class Scene {
public:
	Scene() {}
	~Scene() {}

	virtual void Initialize() = 0;
	virtual void Update(double dt) = 0;
	virtual void Exit() = 0;
};

#endif