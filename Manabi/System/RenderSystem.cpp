#include "RenderSystem.h"

#include "../Source/Coordinator.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Source/stb_image.h"

#include "../Components/Renderer.h"
#include "../Components/Transform.hpp"

#include "../Source/LoadOBJ.h"
#include "MyMath.h"

//Testing
#include "../Source/Application.h"

extern Coordinator g_coordinator;

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

Vector3 cubePositions[] = {
	Vector3(0.0f,  0.0f,  0.0f),
	Vector3(2.0f,  5.0f, -15.0f),
	Vector3(-1.5f, -2.2f, -2.5f),
	Vector3(-3.8f, -2.0f, -12.3f),
	Vector3(2.4f, -0.4f, -3.5f),
	Vector3(-1.7f,  3.0f, -7.5f),
	Vector3(1.3f, -2.0f, -2.5f),
	Vector3(1.5f,  2.0f, -2.5f),
	Vector3(1.5f,  0.2f, -1.5f),
	Vector3(-1.3f,  1.0f, -1.5f)
};

void RenderSystem::Initialize() {
	shader.Initialize("Shader/default.vert", "Shader/default.frag");

	//glGenVertexArrays(1, &m_vertexArrayObject);

	m_camera = g_coordinator.CreateEntity();

	//g_coordinator.AddComponent(m_camera, Transform{ .position = Vector3(0, 0, 10), .rotation = Vector3(0, 1, 0), .scale = Vector3(1, 1, 1) });
	g_coordinator.AddComponent(m_camera, Camera{ .position = Vector3(0, 0, 10), .rotation = Vector3(0, 1, 0), .target = Vector3(0, 0, -1) });

	camera = g_coordinator.GetComponent<Camera>(m_camera);
	camera.projection_matrix.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	camera.SetVars();

	for (auto const& entity : m_entities) {
		//auto renderer = g_coordinator.GetComponent<Renderer>(entity);
		//
		//std::vector<Position> vertices;
		//std::vector<TexCoord> uvs;
		//std::vector<Vector3> normals;
		//bool success = LoadOBJ(renderer.file_path.c_str(), vertices, uvs, normals);
		//if (!success) {
		//	std::cout << "OBJ Load Failed" << std::endl;
		//	return;
		//}

		//std::vector<Vertex> vertex_buffer_data;
		//std::vector<GLuint> element_buffer_data;

		//IndexVBO(vertices, uvs, normals, element_buffer_data, vertex_buffer_data);

		//Mesh* mesh = new Mesh();
		//mesh->m_mode = Mesh::DRAW_TRIANGLES;

		//glBindBuffer(GL_ARRAY_BUFFER, mesh->m_vertexBufferObject);
		//glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_elementBufferObject);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_buffer_data.size() * sizeof(GLuint), &element_buffer_data[0], GL_STATIC_DRAW);

		//mesh->m_elementSize = element_buffer_data.size();
		//renderer.mesh = mesh;
	}

	//unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("./Textures/container.jpg", &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	shader.Use();

	shader.SetMat4("projection", camera.projection_matrix);
}

void RenderSystem::Update(double dt) {

	// Camera
	if (Application::IsKeyPressed('W')) {
		camera.position += 2.0f * camera.target * dt;
	}
	if (Application::IsKeyPressed('A')) {
		camera.position -= 2.0f * (camera.target.Cross(camera.up)).Normalize() * dt;
	}	
	if (Application::IsKeyPressed('S')) {
		camera.position -= 2.0f * camera.target * dt;
	}	
	if (Application::IsKeyPressed('D')) {
		camera.position += 2.0f * (camera.target.Cross(camera.up)).Normalize() * dt;
	}

	{
		float xPos = static_cast<float>(Application::mouse_current_x);
		float yPos = static_cast<float>(Application::mouse_current_y);

		float xOffSet = xPos - camera.lastX;
		float yOffSet = yPos - camera.lastY;
		camera.lastX = xPos;
		camera.lastY = yPos;

		float sensitivity = 0.1f;
		xOffSet *= sensitivity;
		yOffSet *= sensitivity;

		camera.yaw += xOffSet;
		camera.pitch += yOffSet;


		if (camera.pitch > 89.0f)
			camera.pitch = 89.0f;
		if (camera.pitch < -89.0f)
			camera.pitch = -89.0f;

		Vector3 front;
		front.x = cos(Math::DegreeToRadian(camera.yaw));// cos(Math::DegreeToRadian(camera.pitch));
		front.y = sin(Math::DegreeToRadian(camera.pitch));
		front.z = -sin(Math::DegreeToRadian(camera.yaw));// * cos(Math::DegreeToRadian(camera.pitch));

		std::cout << front << std::endl;
		camera.target = front;
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture);

	//shader.Use();

	Mtx44 view;
	view.SetToIdentity();
//	view.SetToLookAt(camera.position.x, camera.position.y, camera.position.z, 
//		camera.position.x + camera.target.x, camera.position.y + camera.target.y, camera.position.z - camera.target.z,
//		camera.up.x, camera.up.y, camera.up.z);
	view.SetToLookAt(camera.position.x, camera.position.y, camera.position.z,
		camera.position.x + camera.target.x, camera.position.y + camera.target.y, camera.position.z + camera.target.z,
		camera.up.x, camera.up.y, camera.up.z);
	//shader.SetMat4("model", model);
	shader.SetMat4("view", view);

	glBindVertexArray(VAO);

	for (unsigned int i = 0; i < 10; i++) {
		Mtx44 modelTrans, modelRot, model;
		modelTrans.SetToIdentity();
		modelRot.SetToIdentity();
		model.SetToIdentity();
		modelTrans.SetToTranslation(cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
		//modelTrans.SetToTranslation(-1.5f, -2.2f, -15.5f);
		float angle = 20.0f * i;
		modelRot.SetToRotation(angle, 1.0f, 0.3f, 0.5f);
		model = modelTrans * modelRot;
		shader.SetMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	//for (auto const entity : m_entities) {

		//Mesh *mesh = g_coordinator.GetComponent<Renderer>(entity).mesh;
		//RenderMesh(mesh);

		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

		//glBindTexture(GL_TEXTURE_2D, texture);
		//glBindVertexArray(m_vertexArrayObject);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//}
}

void RenderSystem::RenderMesh(Mesh* mesh) {
	Mtx44 model, view, projection;

	model.SetToIdentity();
	view.SetToIdentity();
	view.SetToTranslation(0, 0, -3);
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);

	//shader.SetMat4("projection", projection);
	//shader.SetMat4("view", view);
	//shader.SetMat4("model", model);

	mesh->Render();
}