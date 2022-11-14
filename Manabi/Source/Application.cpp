#include <glad/glad.h>

#include "Application.h"
#include "Shader.h"

#include "TestScene.h"

Window* Application::m_context = nullptr;
double Application::mouse_current_x = 0.0, Application::mouse_current_y = 0.0;

//Shortcut to be changed
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	Application::mouse_current_x = xposIn;
	Application::mouse_current_y = yposIn;
}

Application::Application() 
{
}

Application::~Application()
{
}

void Application::Init() {
	m_context = new Window("Test", 1920, 1080);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glfwSetCursorPosCallback(m_context->GetWindow(), mouse_callback);
}

void Application::Run() {
	Scene* scene = new TestScene();
	scene->Initialize();

	m_timer.Start();
	while (!glfwWindowShouldClose(m_context->GetWindow())) {
		m_timer.Update();
		scene->Update(m_timer.GetDeltaTime());

		m_context->SwapBuffers();
		glfwPollEvents();
	}
}

void Application::Exit() {
	delete(m_context);
	glfwTerminate();
}

bool Application::IsKeyPressed(unsigned short key) {
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}