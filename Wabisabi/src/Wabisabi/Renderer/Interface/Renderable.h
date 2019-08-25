#pragma once
#include "Wabisabi/Types.h"
#include <glm/gtc/matrix_access.hpp>
namespace Wabisabi
{
	class Renderable
	{
	public:
		virtual ~Renderable() = default;
		/*virtual std::vector<Mesh>::iterator begin() = 0;
		virtual std::vector<Mesh>::iterator end() = 0;
		virtual std::vector<Mesh>::const_iterator begin() const = 0;
		virtual std::vector<Mesh>::const_iterator end() const = 0;*/
		virtual const Float4x4& GetModel() const = 0;
		virtual const Float4& GetPosition() const { return glm::column(GetModel(),4); }
		bool operator==(const Renderable& other)
		{
			//auto other_it = other.begin();
			//for (auto it = this->begin(); it != this->end() && other_it != other.end() ; it++)
			//{
			//	//if()
			//}
		}
	};

}
