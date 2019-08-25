#pragma once
#include "wbpch.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <filesystem>
#include "Log.h"
#include <glm/glm.hpp>
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"
#include "Renderer/Texture.h"
#ifdef WB_DEBUG
	#include <chrono>
#endif // WB_DEBUG
namespace Wabisabi
{
	class Loader
	{
	public:
		static std::pair<std::string, std::string> LoadShaderPair(const std::string& vertexpath, const std::string& fragmentpath)
		{
			std::string vertex = ShaderPreprocessor(LoadShader(vertexpath),vertexpath);
			std::string fragment = ShaderPreprocessor(LoadShader(fragmentpath),fragmentpath);
			return std::move(std::make_pair(vertex , fragment));
		}
		static std::string LoadShader(const std::string& path)
		{
			std::ifstream file(path);
			std::stringstream buffer;
			buffer << file.rdbuf();
			return std::move(buffer.str());
		}

		static void LoadObj(const std::string& path,std::vector<Mesh>& meshes, std::vector<Material>& materials)
		{
			WB_CORE_TIMER_INIT();
			std::thread* thd = nullptr;
			std::vector<glm::vec3> vertexCoordinates;
			std::vector<glm::vec2> textureCoordinates;
			std::vector<glm::vec3> normalCoordinates; 
			struct Indices
			{
				std::string MeshName;
				std::string MaterialName;
				std::vector<int> Vertex;
				std::vector<int> Texture;
				std::vector<int> Normal;
				Indices(const std::string& name) : MeshName(name) {};
				Indices() {};
			};
			std::vector<Indices> indices(1);
			std::vector<MaterialTexure> subMaterial;
			std::string materialPath;

			WB_CORE_TIMER_START();
			std::ifstream file(path);
			std::string line;
			std::string pattern;
			float x = 0, y = 0 , z = 0;
			uint32_t lineCount = 1;
			
			while (std::getline(file, line))
			{
				auto beginit = line.begin();
				while (beginit != line.end() && (*beginit == ' ' || *beginit == '\t')) beginit++;
				auto it = beginit;
				while (it != line.end() && *it != ' ' ) it++;
				std::string word(beginit, it);
				if (word == "v")
				{
					if (!(std::istringstream(std::string(it, line.end())) >> x >> y >> z))
					{
						WB_CORE_WARN("Obj Parse Error line : {0} : {1}", lineCount,line);
					}
					vertexCoordinates.emplace_back(x,y,z);
				}
				else if (word == "vn")
				{
					if (!(std::istringstream(std::string(it, line.end())) >> x >> y >> z))
					{
						WB_CORE_WARN("Obj Parse Error line : {0} : {1}", lineCount, line);
					}
					normalCoordinates.emplace_back(glm::normalize(glm::vec3(x,y,z)));
				}
				else if (word == "vt")
				{
					if (!(std::istringstream(std::string(it, line.end())) >> x >> y) )
					{
						WB_CORE_WARN("Obj Parse Error line : {0} : {1}", lineCount, line);
					}
					textureCoordinates.emplace_back(x, y);
				}
				else if (word == "f")
				{
					if (pattern.empty())
					{
						uint8_t  numCheked = false;
						uint8_t count = 0;
						while (*it == ' ') it++;
						auto localIt = it;
						while (*localIt != ' ')
						{
							if (*localIt == '/')
							{
								pattern += ('/');
								numCheked = false;
							}
							else if (!numCheked)
							{
								if (count == 0) pattern += 'v';
								else if (count == 1) pattern += 't';
								else if (count == 2) pattern += 'n';

								numCheked = true;
								count++;
							}

							localIt++;
						}
						pattern += " ";
					}
					auto patternIt = pattern.cbegin();
					//auto beginIt = it + 1;
					while (*it == ' ') it++;
					std::string number;
					Indices& localIndicies = indices.back();
					while (it != line.end())
					{
						if (patternIt + 1 == pattern.end())
						{
							patternIt = pattern.begin();
							while (it != line.end() && *it == ' ') it++;
							if (it == line.end()) break;
						}
						if (*patternIt == 'v')
						{
							number = Word(it, line.end(), *(patternIt + 1));
							//vertexIndices.back().second.push_back(std::atoi(number.c_str()) - 1);
							localIndicies.Vertex.push_back(std::atoi(number.c_str()) - 1);
							//indices.back().Vertex.push_back(std::atoi(number.c_str()) - 1);
						}
						else if (*patternIt == 't')
						{
							number = Word(it, line.end(), *(patternIt + 1));
							//textureIndices.back().push_back(std::atoi(number.c_str()) - 1);
							localIndicies.Texture.push_back(std::atoi(number.c_str()) - 1);
							//indices.back().Texture.push_back(std::atoi(number.c_str()) - 1);
						}
						else if (*patternIt == 'n')
						{
							number = Word(it, line.end(), *(patternIt + 1));
							//normalIndices.back().push_back(std::atoi(number.c_str()) - 1);
							localIndicies.Normal.push_back(std::atoi(number.c_str()) - 1);
							//indices.back().Normal.push_back(std::atoi(number.c_str()) - 1);
						}
						else if (*patternIt == '/')
						{
							it++;
						}

						patternIt++;
					}
					//WB_CORE_ASSERT();
					auto fullTriangleCount = localIndicies.Vertex.size() / 3;
					auto partialTriangleCount = localIndicies.Vertex.size() % 3; //TODO rewrite 
					if (partialTriangleCount != 0)
					{
						for (size_t i = 0; i < partialTriangleCount; i++)
						{
							auto beginIt = localIndicies.Vertex.begin() + fullTriangleCount * 3 - 3;
							//localIndicies.Vertex.insert();
						}
					}

				}
				else if (word == "o")
				{
				while (it != line.end() && *it == ' ') it++;
				auto begin = it;
				while (it != line.end() && *it != ' ') it++;
				std::string meshName = std::string(begin, it);
				if (!indices.back().Vertex.empty())
				{
					indices.emplace_back(meshName);
				}
				else
				{
					indices.back().MeshName = meshName;
					indices.back().Normal.clear();
					indices.back().Texture.clear();
				}
				}
				else if (word == "mtllib")
				{
					std::string materialFile = Word(it, line.end(), '\0');
					std::filesystem::path root(path);
					root.replace_filename(materialFile);
					materialPath = root.string();
				}
				else if (word == "usemtl")
				{
					std::string materialName = Word(it, line.end(), ' ');
					indices.back().MaterialName = materialName;
					subMaterial.push_back(LoadOneMaterial(materialPath, materialName));
				}
				lineCount++;
			}
			for (auto& it = subMaterial.begin(); it != subMaterial.end() ; it++) // Texture creating
			{
				auto res = std::find_if(subMaterial.begin(), it, [it](const MaterialTexure& el) { return el.DiffusePath == (*it).DiffusePath; });
				if (res != it) it->Diffuse = res->Diffuse; else it->Diffuse.reset(Texture::Create(it->DiffusePath.string()));

				res = std::find_if(subMaterial.begin(), it, [it](const MaterialTexure& el) { return el.SpecularPath == (*it).SpecularPath; });
				if (res != it) it->Specular = res->Specular; else it->Specular.reset(Texture::Create(it->SpecularPath.string()));

				res = std::find_if(subMaterial.begin(), it, [it](const MaterialTexure& el) { return el.NormalPath == (*it).NormalPath; });
				if (res != it) it->Normal = res->Normal; else it->Normal.reset(Texture::Create(it->NormalPath.string()));
			}
			for (Indices& el : indices)
			{
				WB_CORE_ASSERT(el.Vertex.size() >= el.Texture.size() || el.Vertex.size() >= el.Normal.size(), path);
				auto vertexMax = std::max_element(el.Vertex.cbegin(), el.Vertex.cend()); 
				auto textureMax = std::max_element(el.Texture.cbegin(), el.Texture.cend());
				auto normalMax = std::max_element(el.Normal.cbegin(), el.Normal.cend());
				for (size_t i = 0; i < el.Vertex.size(); i++)
				{
					if (el.Vertex[i] < 0)
					{
						el.Vertex[i] = *vertexMax - el.Vertex[i] + 2;
					}
					if (textureMax != el.Texture.end() && el.Texture[i] < 0)
					{
						el.Texture[i] = *textureMax - el.Texture[i] + 2;
					}
					if (normalMax != el.Normal.end() && el.Normal[i] < 0)
					{
						el.Normal[i] = *normalMax - el.Normal[i] + 2;
					}
				}
			}
			for (Indices& el : indices)
			{
				meshes.emplace_back(vertexCoordinates, textureCoordinates, normalCoordinates, el.Vertex, el.Texture, el.Normal);
				meshes.back().SetName(el.MeshName);
				int res = -1;
				for (size_t i = 0; i < subMaterial.size();i++)
				{
					if (subMaterial[i].Name == el.MaterialName)
					{
						res = static_cast<int>(i);
					}
				}
				meshes.back().SetMaterialId(res);
			}
			for (const auto& el : subMaterial)
			{
				materials.emplace_back(el.Diffuse, el.Specular, el.Shiness, el.Normal);
				materials.back().SetName(el.Name);
			}
			
			WB_CORE_TIMER_END();
			WB_CORE_TRACE("File {0}: Loading Duration : {1} milliseconds",path, WB_CORE_TIMER_END_MINUS_START(milliseconds));
		}
		static void LoadMtl(const std::string& filePath,std::vector<Material>& materials)
		{
			std::filesystem::path path(filePath);
			std::ifstream file(path);
			std::string line;
			std::vector<MaterialTexure> textures; 
			while (std::getline(file, line))
			{
				auto beginit = line.begin();
			
				while (beginit != line.end() && (*beginit == ' ' || *beginit == '\t')) beginit++;
				auto it = beginit;
				while (it != line.end() && *it != ' ') it++;
				std::string word(beginit, it);
				if (word == "newmtl")
				{
					textures.emplace_back(Word(it, line.end(), ' '));
				}
				else if (word == "Ns")
				{
					textures.back().Shiness = std::atof(Word(it, line.end(), ' ').c_str());
				}
				else if (word == "map_Kd")
				{
					path.replace_filename(Word(it, line.end(), '\0'));
					textures.back().Diffuse.reset(Texture::Create(path.string()));
				}
				else if (word == "map_Ks")
				{
					path.replace_filename(Word(it, line.end(), '\0'));
					textures.back().Specular.reset(Texture::Create(path.string()));
				}
				else if (word == "map_Bump")
				{
					path.replace_filename(Word(it, line.end(), '\0'));
					textures.back().Normal.reset(Texture::Create(path.string()));
				}
			}

			for (const auto& el : textures)
			{
				materials.emplace_back(el.Diffuse, el.Specular,el.Shiness,el.Normal);
				materials.back().SetName(el.Name);
			}
		}
		static void FreePair(const char* vertexsrc, const char* fragmentsrc)
		{
			delete[] vertexsrc;
			delete[] fragmentsrc;
		}
	private:
		struct MaterialTexure
		{
			std::string Name;
			double Shiness;
			float Transparency;
			RGBA AmbientIntensvity;
			RGBA DiffuseIntensvity;
			RGBA SpecualarIntensvity;
			std::shared_ptr<Texture> Diffuse;
			std::filesystem::path DiffusePath;
			std::shared_ptr<Texture> Specular;
			std::filesystem::path SpecularPath;
			std::shared_ptr<Texture> Normal;
			std::filesystem::path NormalPath;
			MaterialTexure(const std::string& name) :Name(name), Diffuse(nullptr), Specular(nullptr), Normal(nullptr), Shiness(0) {};
			MaterialTexure() : Diffuse(nullptr), Specular(nullptr), Normal(nullptr), Shiness(0) {};
		};
		static MaterialTexure LoadOneMaterial(const std::string& globalPath, const std::string& name)
		{
			std::filesystem::path path(globalPath);
			std::ifstream file(globalPath);
			std::string line;
			std::string word("");
			std::string materialName("");
			MaterialTexure subMaterial;
			while (materialName != name && std::getline(file,line))
			{
				std::istringstream(line) >> word >> materialName;
			}
			if (!file.eof())
			{
				word.clear();
				subMaterial.Name = materialName;
				float x = 0 , y = 0, z = 0;
				while (word != "newmtl" && std::getline(file, line))
				{
					auto beginit = line.begin();
					while (beginit != line.end() && (*beginit == ' ' || *beginit == '\t')) beginit++;
					auto it = beginit;
					while (it != line.end() && *it != ' ') it++;
					word = std::string(beginit, it);

					if (word == "Ns")
					{
						subMaterial.Shiness = std::atof(Word(it, line.end(), ' ').c_str());
					}
					else if (word == "Ka")
					{
						if (!(std::istringstream(std::string(it, line.end())) >> x >> y >> z))
						{
							WB_CORE_WARN("Material file parse error path : {0} material {1} property {2}", globalPath, materialName,word);
							subMaterial.AmbientIntensvity = RGBA(0.f);
						}
						else subMaterial.AmbientIntensvity = RGBA(x,y,z,1.f);
					}
					else if (word == "Kd")
					{
						if (!(std::istringstream(std::string(it, line.end())) >> x >> y >> z))
						{
							WB_CORE_WARN("Material file parse error path : {0} material {1} property {2}", globalPath, materialName, word);
							subMaterial.DiffuseIntensvity = RGBA(0.f);
						}
						else subMaterial.DiffuseIntensvity = RGBA(x, y, z, 1.f);
					}
					else if (word == "Ks")
					{
						if (!(std::istringstream(std::string(it, line.end())) >> x >> y >> z))
						{
							WB_CORE_WARN("Material file parse error path : {0} material {1} property {2}", globalPath, materialName, word);
							subMaterial.SpecualarIntensvity = RGBA(0.f);
						}
						else subMaterial.SpecualarIntensvity = RGBA(x, y, z, 1.f);
						
					}
					else if (word == "d")
					{
						if (!(std::istringstream(std::string(it, line.end())) >> x))
						{
							WB_CORE_WARN("Material file parse error path : {0} material {1} property {2}", globalPath, materialName, word);
							subMaterial.Transparency = 1.f;
						}
						else subMaterial.Transparency = x;
					}
					else if (word == "Tr")
					{
						if (!(std::istringstream(std::string(it, line.end())) >> x))
						{
							WB_CORE_WARN("Material file parse error path : {0} material {1} property {2}", globalPath, materialName, word);
							subMaterial.Transparency = 1.f;
						}
						else subMaterial.Transparency = 1.f - x;
					}
					else if (word == "map_Kd")
					{
						path.replace_filename(Word(it, line.end(), '\0'));
						subMaterial.DiffusePath = path;
						//subMaterial.Diffuse = Texture::Create(path.string());
					}
					else if (word == "map_Ks")
					{
						path.replace_filename(Word(it, line.end(), '\0'));
						subMaterial.SpecularPath = path;
						//subMaterial.Specular = Texture::Create(path.string());
					}
					else if (word == "map_Bump")
					{
						path.replace_filename(Word(it, line.end(), '\0'));
						subMaterial.NormalPath = path;
						//subMaterial.Normal = Texture::Create(path.string());
					}
				}
			}
			else
			{
				WB_CORE_TRACE("Material load failed name:{0} file:{1}", name, globalPath);
			}
			return subMaterial;
		}
		static std::string Word(std::string::iterator& it, const std::string::iterator& end, const char delimiter)
		{
			while (it != end && (*it == ' '|| *it == '\t')) it++;
			std::string::iterator saveIt = it;
			while (it != end && *it != delimiter)
			{
				it++;
			}
			std::string str(saveIt , it);
			
			return std::move(str);
		}
		static std::string ShaderPreprocessor(const std::string& src, const std::string& path)
		{
			std::string root(path);
			size_t found = -1;
			for (auto it = root.rbegin(); it != root.rend(); it++)
			{
				if (*it == '/' || *it == '\\')
				{
					found = it - root.rbegin();
					break;
				}
			}
			if (found != -1)
			{
				root.erase(root.end() - found, root.end());
			}
			else root = "";

			std::string source(src);
			found = source.find("#include");
			while (found != std::string::npos)
			{
				size_t begin = source.find("\"", found);
				size_t end = source.find("\"", begin + 1);
				std::string path = root + std::string(source.begin() + begin + 1, source.begin() + end);

				std::string subsource = LoadShader(path);
				source.erase(found, end - found + 1);
				source.insert(found, subsource);

				found = source.find("#include", found + 1);
			}
			return std::move(source);
		}
	};
}