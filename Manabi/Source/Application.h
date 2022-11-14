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

	static double mouse_current_x, mouse_current_y;
private:
	Core::Timer m_timer;
	static Window* m_context;

	const static int m_window_deadzone = 100;
	const static int m_window_width = 800;
	const static int m_window_height = 600;
};


#endif // !APPLICATION_H