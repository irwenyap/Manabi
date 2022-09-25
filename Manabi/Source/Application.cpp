#include <glad/glad.h>

#include "Application.h"
#include "Shader.h"


#include "TestScene.h"

Application::Application() 
	: m_context(nullptr)
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
}

void Application::Run() {
	Scene* scene = new TestScene();
	scene->Initialize();

	m_timer.Start();
	while (!glfwWindowShouldClose(m_context->GetWindow())) {

		scene->Update(m_timer.GetDeltaTime());
		scene->Render();

		m_context->SwapBuffers();
		glfwPollEvents();
	}
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	//shader.Delete();
}

void Application::Exit() {
	delete(m_context);
	glfwTerminate();
}