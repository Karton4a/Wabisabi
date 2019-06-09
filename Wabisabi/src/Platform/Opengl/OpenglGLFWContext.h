#pragma once
#include "Wabisabi/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Wabisabi
{
	class OpenglGLFWContext : public GraphicContext
	{
		
	public:
		OpenglGLFWContext(GLFWwindow* window);
		virtual void Init() override final;
		virtual void SwapBuffers() override final;
	private:
		GLFWwindow* m_Window;
	};
}