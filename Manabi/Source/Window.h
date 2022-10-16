#ifndef WINDOW_H
#define WINDOW_H

#include <glfw/glfw3.h>

#include <iostream>

class Window
{
public:
	Window(const char* title, int width, int height);
	~Window();

	GLFWwindow* GetWindow() const;
	void SwapBuffers();
private:
	GLFWwindow* m_window;
	int m_width, m_height;
	const char* m_title;

	void Init();
};

#endif