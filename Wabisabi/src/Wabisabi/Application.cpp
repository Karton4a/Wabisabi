#include "wbpch.h"
#include "Application.h"

#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"

#include <glad/glad.h>
#include <stb/stb_image.h>


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
			"layout (location = 2) in vec2 texCoord;\n"
			"out vec4 u_Color;\n"
			"out vec2 v_TexCoord;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"u_Color = color;\n"
			"v_TexCoord = texCoord;\n"
			"}\0";
		const GLchar* fragmentShaderSource = "#version 330 core\n"
			"out vec4 color;\n"
			"uniform vec4 ourColor;"
			"uniform sampler2D u_Texture;"
			"in vec4 u_Color;\n"
			"in vec2 v_TexCoord;\n"
			"void main()\n"
			"{\n"
			"color = texture(u_Texture,v_TexCoord);\n"
			"}\n\0";

		m_Shader.reset(new OpenglShader(vertexShaderSource, fragmentShaderSource));
		//m_Shader->Bind();
		m_Shader->SetUniform4f("ourColor", 1.f, 1.f, .0f, 1.f);

		GLfloat vertices[] = {
			 0.3f,  0.5f, 0.0f,1.f,0.f,0.f,1.f, 1.f,0.f, // Top Right
			 0.3f, -0.5f, 0.0f,1.f,1.f,0.f,1.f, 1.f,1.0f,  // Bottom Right
			-0.3f, -0.5f, 0.0f,1.f,0.f,1.f,1.f, 0.f,1.0f,  // Bottom Left
			-0.3f,  0.5f, 0.0f,1.f,1.f,1.f,1.f, 0.f,0.f,  // Top Left 
		};
		GLuint indices[] = {  // Note that we start from 0!
			0, 1, 3,  // First Triangle
			1, 2, 3   // Second Triangle
		};
		
		BufferLayout layout = {

			{ShaderDataType::Float3,"position"},
			{ShaderDataType::Float4,"color"},
			{ShaderDataType::Float2,"texture"},
		};

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
		
		int width = 0, height = 0, bpp = 0;
		char* data = (char*)stbi_load("C:/Users/anpas/source/repos/Wabisabi/texture/logo.png", &width, &height, &bpp, 4);
		unsigned int textureid = 0;
		glCreateTextures(GL_TEXTURE_2D, 1, &textureid);
		glBindTexture(GL_TEXTURE_2D, textureid);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		if (data)
			stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureid);
		m_Shader->SetUniform1i("u_Texture", 0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		while (m_Running)
		{	
			glClearColor(1.f,1.f,1.f,1.f);
			glClear(GL_COLOR_BUFFER_BIT);


			m_Shader->Bind();
			m_VAO->Bind();
			
			glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
			

			for (auto el : m_LayerStack)
			{
				el->OnUpdate();
			}
			m_Window->OnUpdate();	
		}
		glDeleteTextures(1, &textureid);
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