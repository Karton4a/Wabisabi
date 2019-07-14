#include "wbpch.h"
#include "WindowsWindow.h"
#include "Wabisabi/Log.h"
#include "Wabisabi/Events/KeyEvent.h"
#include "Wabisabi/Events/MouseEvent.h"
#include "Wabisabi/Events/WindowEvent.h"
#include "Platform/Opengl/OpenglGLFWContext.h"
#include <glad/glad.h>

namespace Wabisabi 
{
	static bool s_GLFWInit = false;
	unsigned int WindowsWindow::s_objCount = 0;
	static void GLFWErrorCallback(int error, const char* description)
	{
		WB_CORE_ERROR("GLFW Error:{0}, {1}", error, description);
	}
	Window* Window::Create(const WindowProps& props)
	{
		WindowsWindow::s_objCount++;
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}
	WindowsWindow::~WindowsWindow()
	{
		Destroy();
	}
	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		
		m_GraphicContext->SwapBuffers();
	}
	void WindowsWindow::SetVSync(bool enabled) 
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
	bool WindowsWindow::isVSync() const
	{
		return m_Data.VSync;
	}
	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}
	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;
		if (!s_GLFWInit)
		{
			
			int success = glfwInit();
			WB_CORE_INFO("GLFW INIT");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInit = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		WB_CORE_INFO("Window Created {0} X {1}",props.Width,props.Height);

		/*glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);*/
		m_GraphicContext = std::shared_ptr<GraphicContext>(new OpenglGLFWContext(m_Window));
		m_GraphicContext->Init();
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		glfwSetKeyCallback(m_Window, 
			[](GLFWwindow* window, int key, int scancode, int action, int mods) 
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressed e(key, 0);
						data.Callback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleased e(key);
						data.Callback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressed e(key, 1);
						data.Callback(e);
						break;
					}
					
				}
			});
		glfwSetCharCallback(m_Window, 
			[](GLFWwindow* window, unsigned int codepoint) {
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				KeyTyped e(codepoint);
				data.Callback(e);
			});
		glfwSetCursorPosCallback(m_Window, 
			[](GLFWwindow* window, double xpos, double ypos) {
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				MouseMoved e(xpos,ypos);
				data.Callback(e);
			});
		glfwSetMouseButtonCallback(m_Window, 
			[](GLFWwindow* window, int button, int action, int mods) {
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressed e(button);
						data.Callback(e);
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleased e(button);
						data.Callback(e);
					}
				}
			});
		glfwSetScrollCallback(m_Window, 
			[](GLFWwindow* window, double xoffset, double yoffset) 
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				MouseScrolled e(xoffset, yoffset);
				data.Callback(e);
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				WindowClose e;
				data.Callback(e);
			});
		glfwSetWindowSizeCallback(m_Window, 
			[](GLFWwindow* window, int width, int height) 
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data.Width = width;
				data.Height = height;
				WindowResize e(width, height);
				data.Callback(e);
			});
		glfwSetWindowPosCallback(m_Window, 
			[](GLFWwindow* window, int xpos, int ypos) 
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				WindowMoved e(xpos, ypos);
				data.Callback(e);
			});
	}
	void WindowsWindow::Destroy()
	{
		WindowsWindow::s_objCount--;
		glfwDestroyWindow(m_Window);
		WB_CORE_INFO("Window Destroyed");
		if (WindowsWindow::s_objCount == 0)
		{
			glfwTerminate();
			WB_CORE_INFO("GLFW Terminated");
			s_GLFWInit = false;
		}
	}
}
