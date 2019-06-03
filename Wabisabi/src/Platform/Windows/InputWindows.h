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
		virtual bool IsKeyPressedImpl(int keycode) override final;
		virtual bool IsMousePressedImpl(int botton) override final;
		virtual std::pair<float, float> MousePositionImpl() override final;
		virtual float MousePositionXImpl() override final;
		virtual float MousePositionYImpl() override final;
	};

}