#include "wbpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"

#include <glad/glad.h>

namespace Wabi {

	Application* Application::s_Instance = nullptr;
	#define BIND_FN(x) std::bind(&Application::##x, this, std::placeholders::_1)

	Application::Application()
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

		const GLchar* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 position;\n"
			"layout (location = 1) in vec4 color;\n"
			"out vec4 u_Color;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"u_Color = color;\n"
			"}\0";
		const GLchar* fragmentShaderSource = "#version 330 core\n"
			"out vec4 color;\n"
			"in vec4 u_Color;\n"
			"void main()\n"
			"{\n"
			"color = u_Color;\n"
			"}\n\0";
		m_Shader.reset(new OpenglShader(vertexShaderSource, fragmentShaderSource));
		GLfloat vertices[] = {
			 0.5f,  0.5f, 0.0f,1.f,0.f,0.f,1.f,  // Top Right
			 0.5f, -0.5f, 0.0f,1.f,1.f,0.f,1.f,  // Bottom Right
			-0.5f, -0.5f, 0.0f,1.f,0.f,1.f,1.f,  // Bottom Left
			-0.5f,  0.5f, 0.0f,1.f,1.f,1.f,1.f,   // Top Left 
		};
		GLuint indices[] = {  // Note that we start from 0!
			0, 1, 3,  // First Triangle
			1, 2, 3   // Second Triangle
		};
		//m_VertexBuff.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {

			{ShaderDataType::Float3,"position"},
			{ShaderDataType::Float4,"color"},
		};
		//m_VertexBuff->SetLayout(layout);
		//m_IndexBuff.reset(IndexBuffer::Create(indices, 6));

		m_VAO.reset(VertexArray::Create());
		m_VAO->AddVertexBuffer(vertices, sizeof(vertices),layout);
		m_VAO->SetIndexBuffer(indices, 6);
	}
	Application::~Application()
	{
		//delete m_Window;
	}
	void Application::Run()
	{
		
		

		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		//glEnableVertexAttribArray(0);
		
		//glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		 // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

		while (m_Running)
		{	
			glClearColor(0.f,0.f,0.f,1.f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw our first triangle
			m_Shader->Bind();
			m_VAO->Bind();
			//glBindVertexArray(VAO);
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
			//glBindVertexArray(0);
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
		//glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		return true;
	}
}