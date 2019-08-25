#pragma once
#include "wbpch.h"
class RenderQueue {};
namespace Wabisabi
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL,
		DirectX,
		Vulkan,
	};
	class Renderer
	{
	public:
		//Get current graphic API (Opengl, DirectX, Vulkan)
		static inline RendererAPI GetAPI() { return s_RendererAPI; }
		//Game object,shader
		//Game object,material
		//va,shader
		//va,material
		//mesh,shader
		//mesh,material
		static void Push();
		// without sorting
		static void PushUnOrdered();
		static void Render();
	private:
		
		static RenderQueue s_RenderQueue;
		static RendererAPI s_RendererAPI;
	};
}