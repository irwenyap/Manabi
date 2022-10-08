#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Window::Window(const char* title, int width, int height) {
	m_window = nullptr;
	m_title = title;
	m_width = width;
	m_height = height;

	Init();
}

Window::~Window() {
	glfwDestroyWindow(m_window);
}

GLFWwindow* Window::GetWindow() const {
	return m_window;
}

void Window::SwapBuffers() {
	glfwSwapBuffers(m_window);
}

void Window::Init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	m_window = glfwCreateWindow(1920, 1080, "Venture", NULL, NULL);
	if (m_window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_window);

	glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
