#include "wbpch.h"
#include "Model.h"
#include "Wabisabi/Loader.h"
namespace Wabisabi
{
	Model::Model(const std::string& path)
	{
		Loader::LoadObj(path, m_Meshes);
	}
}
