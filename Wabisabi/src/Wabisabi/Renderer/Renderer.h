#pragma once
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
		static inline RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}