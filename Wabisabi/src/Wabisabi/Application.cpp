#include "wbpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"

#include <glad/glad.h>

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShaderLoader.h"


namespace Wabi {

	Application* Application::s_Instance = nullptr;
	#define BIND_FN(x) std::bind(&Application::##x, this, std::placeholders::_1)

	Application::Application()
		:m_Camera({0.f,0.f,3.0f},{0.f,0.f,-1.f}, 0.05f,0.04f)
	{
		if (s_Instance != nullptr)
		{
			//TODO Assert or just change s_Instance on new object
			WB_CORE_ERROR("App object already exist");
			__debugbreak();
		}
		s_Instance = this;
		m_Window = std::shared_ptr<Wabi::Window>(Wabi::Window::Create());
		m_Running = true;
		m_Window->SetCallback(BIND_FN(OnEvent));

		auto [vertextest, fragmentest] = ShaderLoader::Load("shaders/shader.vert", "shaders/shader.frag");
		m_Shader.reset(new OpenglShader(vertextest, fragmentest));

		ShaderLoader::Free(vertextest, fragmentest);
		//m_Shader->Bind();

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)m_Window->GetWidth() / (float)m_Window->GetHeight(), 0.1f, 100.0f);
		m_Shader->SetUniformMat4("u_Proj", proj);
		//GLfloat vertices[] = {
		//	//coord				 //textcoord
		//	 0.5f,  0.5, -5.f,  1.f,0.f,    // Top Right
		//	 0.5, -0.5, -5.f,   1.f,1.0f,   // Bottom Right
		//	-0.5, -0.5, -5.f,   0.f,1.0f,   // Bottom Left
		//	-0.5,  0.5, -5.f,   0.f,0.f,    // Top Left
		//};
		GLfloat vertices[] = {
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

		GLuint indices[] = {  // Note that we start from 0!
			0, 1, 3,  // First Triangle
			1, 2, 3   // Second Triangle
		};
		int Heitg = 5;
		BufferLayout layout = {

			{ShaderDataType::Float3,"position"},
			{ShaderDataType::Float2,"texture"},
		};

		m_VAO.reset(VertexArray::Create());
		m_VAO->AddVertexBuffer(vertices, sizeof(vertices),layout);
		//m_VAO->SetIndexBuffer(indices, 6);
	}
	Application::~Application()
	{
		//delete m_Window;
	}
	void Application::Run()
	{
		
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
		m_Shader->SetUniform4f("ourColor", 1.f, 0.f, .0f, 1.f);
		glm::mat4 rot(1.f);

		float oldx = (float)(m_Window->GetWidth() / 2);
		float oldy = (float)(m_Window->GetHeight() / 2);
		Input::SetMousePosition(oldx, oldy);
		Input::HideCursor();

		while (m_Running)
		{	
			glClearColor(1.f, 1.f, 1.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_Shader->Bind();
			m_VAO->Bind();

			glm::mat4 model(1.f);
			rot = glm::rotate(rot, 0.04f, {1.f,1.f,0.f});
			model = glm::translate(model, { 0.f,.0f,-3.f })*rot;
			m_Shader->SetUniformMat4("u_Model", model);
			auto [posX,posY] = Input::MousePosition();
			float offsetX = posX - oldx;
			float offsetY = oldy - posY;

			Input::SetMousePosition(oldx, oldy);

			m_Camera.ProcessRotation(offsetX, offsetY);

			if (Input::IsKeyPressed(WB_KEY_S))
			{
				m_Camera.ProcessMovement(CameraMove::Backward);
			}
			if (Input::IsKeyPressed(WB_KEY_W))
			{
				m_Camera.ProcessMovement(CameraMove::Forward);
			}

			if (Input::IsKeyPressed(WB_KEY_A))
			{
				m_Camera.ProcessMovement(CameraMove::Left);
			}
			if (Input::IsKeyPressed(WB_KEY_D))
			{
				m_Camera.ProcessMovement(CameraMove::Right);
			}
			m_Camera.Update();
			m_Shader->SetUniformMat4("u_View", m_Camera.GetView());
			//glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			for (auto el : m_LayerStack)
			{
				el->OnUpdate();
			}
			m_Window->OnUpdate();	
		}
		
	}
	void Application::Init()
	{
		printf("Base Init\n");
	}
	void Application::Update()
	{
		printf("Base Update\n");
	}
	void Application::Draw()
	{
		printf("Base Draw\n");
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher disp(e);
		disp.Dispatch<WindowClose>(BIND_FN(OnWindowClose));
		disp.Dispatch<WindowResize>(BIND_FN(OnWindowResize));
		disp.Dispatch<KeyPressed>(BIND_FN(OnKeyPressedEvent));
		for (auto it = m_LayerStack.rbegin(); it !=m_LayerStack.rend() ; it++)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	bool Application::OnWindowClose(WindowClose& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResize& e)
	{
		glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		return true;
	}
	bool Application::OnKeyPressedEvent(KeyPressed& e)
	{
		if (e.GetKeyCode() == WB_KEY_ESCAPE)
			m_Running = false;
		
		return true;
	}
}