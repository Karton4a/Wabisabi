#pragma once
#include "wbpch.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "Log.h"
#include <glm/glm.hpp>
#include "Renderer/Mesh.h"
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

		static void LoadObj(const std::string& path,std::vector<Mesh>& meshes)
		{
			WB_CORE_TIMER_INIT();

			std::vector<glm::vec3> vertexCoordinates;
			std::vector<glm::vec2> textureCoordinates;
			std::vector<glm::vec3> normalCoordinates; 
			//std::vector<std::pair<std::string, std::array< std::vector<unsigned int> ,3> > > vertexIndices;
		
			std::vector<std::pair<std::string, std::vector<unsigned int>>> vertexIndices(1);
			std::vector<std::vector<unsigned int>> textureIndices(1);
			std::vector<std::vector<unsigned int>> normalIndices(1);
			WB_CORE_TIMER_START();
			std::ifstream file(path);
			std::string line;
			std::string pattern;
			float x = 0, y = 0 , z = 0;
			uint32_t lineCount = 1;
			
			while (std::getline(file, line))
			{
				auto it = line.begin();
				while (it != line.end() && *it != ' ' ) it++;
				std::string word(line.begin(), it);
				if (lineCount == 9966 - 1)
				{
					char c = 1;
				}
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
								else if(count == 2) pattern += 'n';

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
					while(it != line.end())
					{
						if (patternIt + 1 == pattern.end())
						{
							patternIt = pattern.begin();
							while(it != line.end() && *it == ' ') it++;
							if (it == line.end()) break;
						}
						if (*patternIt == 'v')
						{	
							number = Word(it, line.end(), *(patternIt + 1));
							vertexIndices.back().second.push_back(std::atoi(number.c_str()) - 1);
						}
						else if (*patternIt == 't')
						{
							number = Word(it, line.end(), *(patternIt + 1));
							textureIndices.back().push_back(std::atoi(number.c_str()) - 1);
						}
						else if (*patternIt == 'n')
						{
							number = Word(it, line.end(), *(patternIt + 1));
							normalIndices.back().push_back(std::atoi(number.c_str()) - 1);
						}
						else if (*patternIt == '/')
						{
							it++;
						}
						
						patternIt++;
					}
				}
				else if (word == "o")
				{
					while (it != line.end() && *it == ' ') it++;
					auto begin = it;
					while (it != line.end() && *it != ' ') it++;
					std::string meshName = std::string(begin, it);
					if (!vertexIndices.back().second.empty())
					{
						vertexIndices.emplace_back(meshName, std::vector<unsigned int>());
					}
					else
					{
						vertexIndices.back().first = meshName;
					}
					if (!textureIndices.back().empty())
					{
						textureIndices.emplace_back();
					}
					if (!normalIndices.back().empty())
					{
						normalIndices.emplace_back();
					}
				}
				lineCount++;
			}
			for (size_t i = 0; i < vertexIndices.size(); i++)
			{
				meshes.emplace_back(vertexCoordinates, textureCoordinates, normalCoordinates, vertexIndices[i].second,
					(textureIndices.size()> i) ? textureIndices[i] : std::vector<unsigned int>(),
					(normalIndices.size() > i) ? normalIndices[i] : std::vector<unsigned int>());
				meshes[i].SetName(vertexIndices[i].first);
			}
			
			WB_CORE_TIMER_END();
			WB_CORE_TRACE("File {0}: Loading Duration : {1} milliseconds",path, WB_CORE_TIMER_END_MINUS_START(milliseconds));
		
			size_t memory = textureCoordinates.size() * sizeof(glm::vec2) + sizeof(glm::vec3) * (normalCoordinates.size() + vertexCoordinates.size())
				+ (vertexIndices.size() + textureIndices.size() + normalIndices.size()) * sizeof(unsigned int);
			WB_CORE_TRACE("File {0}: Memory used : {1} bytes",path,memory);
		}
		static void FreePair(const char* vertexsrc, const char* fragmentsrc)
		{
			delete[] vertexsrc;
			delete[] fragmentsrc;
		}
	private:
		static std::string Word(std::string::iterator& it, const std::string::iterator& end, const char delimiter)
		{

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