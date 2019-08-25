#pragma once
#include <list>
#include "VertexArray.h"
#include "Shader.h"
#include "Wabisabi/Types.h"
#include "Camera.h"
#include "Material.h"
#include "Wabisabi/Core.h"
#include "Model.h"
namespace Wabisabi
{
	class RendererComandQueue
	{
	public:

		RendererComandQueue() = default;
		~RendererComandQueue() = default;
		const RendererComandQueue operator=(const RendererComandQueue& other) = delete;
		void Push(Ref<VertexArray>& va,Camera& camera, Float4x4& model = Float4x4(1.f));
		void Push(Model& model, Camera& camera);
		void Push(Mesh& mesh,Material& material, Camera& camera);
	private:
		struct RendererObject
		{
			Ref<VertexArray> Va = nullptr;
			Ref<Shader> Shader = nullptr;
			Float4x4 Model = Float4x4(1.f);
			Float4 Position = Float4(0.f);
			Camera& Camera;
			Material& Material;
			bool IsEnabled = true;
		};
		using Queue = std::list<RendererObject>;
		Queue m_Queue;
		Queue::iterator m_UnOrderedIt = m_Queue.begin();
	};
}