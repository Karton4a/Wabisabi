#pragma once
#include "wbpch.h"
#include "Wabisabi/Input.h"

namespace Wabisabi
{
	
	class WindowsInput : public Input
	{
	public:
		WindowsInput() {};
	private:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMousePressedImpl(int botton) override;
		virtual std::pair<float, float> MousePositionImpl() override;
		virtual float MousePositionXImpl() override;
		virtual float MousePositionYImpl() override;
		virtual void SetMousePositionImpl(float x, float y) override;
		virtual void HideCursorImpl(bool var) override;
	};

}