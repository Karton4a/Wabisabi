#include "wbpch.h"
#include "InputWindows.h"
#include "Wabisabi/Application.h"
#include <GLFW/glfw3.h>
namespace Wabisabi
{
	Input* Input::s_Instance = new WindowsInput();
	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMousePressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::MousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}
	float WindowsInput::MousePositionXImpl()
	{
		auto [x, y] = MousePositionImpl();
		return x;
	}
	float WindowsInput::MousePositionYImpl()
	{
		auto [x, y] = MousePositionImpl();
		return y;
	}
	void WindowsInput::SetMousePositionImpl(float x, float y)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwSetCursorPos(window, x, y);
	}
	void WindowsInput::HideCursorImpl(bool var)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwSetInputMode(window, GLFW_CURSOR, (var)?GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
	}
}

