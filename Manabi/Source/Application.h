#ifndef APPLICATION_H
#define APPLICATION_H

#include "Timer.h"
#include "Window.h"

class Application
{
public:	
	static Application& GetInstance() {
		static Application app;
		return app;
	}
	Application();
	~Application();

	void Init();
	void Run();
	void Exit();

	static bool IsKeyPressed(unsigned short key);
private:
	Core::Timer m_timer;

	Window* m_context;
};


#endif // !APPLICATION_H