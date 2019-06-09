#include "wbpch.h"
#include "OpenglGLFWContext.h"
#include <glad/glad.h>
#include "Wabisabi/Log.h"
namespace Wabisabi
{
	OpenglGLFWContext::OpenglGLFWContext(GLFWwindow* window)
		:m_Window(window)
	{
	}
	void OpenglGLFWContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		WB_CORE_ASSERT(status, "Glad initilization error");
		WB_CORE_INFO("Opengl Version {0}",glGetString(GL_VERSION));
		WB_CORE_INFO("Opengl Vendor {0}", glGetString(GL_VENDOR));
		WB_CORE_INFO("Opengl Renderer Name {0}", glGetString(GL_RENDERER));
	}

	void OpenglGLFWContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}
