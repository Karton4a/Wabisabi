#pragma once
#include"wbpch.h"
#include "Wabisabi/Core.h"
namespace Wabisabi
{
	class WABI_API Input
	{
	public:
		inline static Input* Get() { return s_Instance; }
		static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); };
		static bool IsMousePressed(int key) { return s_Instance->IsKeyPressedImpl(key); };
		static std::pair<float, float> MousePosition() { return s_Instance->MousePositionImpl(); }
		static float MousePositionX() { return s_Instance->MousePositionXImpl(); };
		static float MousePositionY() { return s_Instance->MousePositionYImpl(); };
		static void SetMousePosition(float x,float y) { return s_Instance->SetMousePositionImpl(x,y); };
		static void HideCursor(bool var = true) { return s_Instance->HideCursorImpl(var); };
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMousePressedImpl(int key) = 0;
		virtual std::pair<float, float> MousePositionImpl() = 0;
		virtual float MousePositionXImpl() = 0;
		virtual float MousePositionYImpl() = 0;
		virtual void SetMousePositionImpl(float x, float y) = 0;
		virtual void HideCursorImpl(bool var) = 0;
		Input() {};
	private:
		static Input* s_Instance;
	};

}
