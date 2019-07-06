#pragma once
#include "wbpch.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "Log.h"
#include <glm/glm.hpp>
#include "Renderer/Mesh.h"
#include <chrono>
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
			//FILE* shader = NULL;
			//fopen_s(&shader,vertexpath.c_str(), "rb");

			//fseek(shader, 0L, SEEK_END);
			//unsigned long len = ftell(shader);
			////int len = 0;
			///*char ch = 1;
			//while (!feof(shader))
			//{
			//	fread(&ch, sizeof(char), 1, shader);
			//	len++;
			//}*/
			//rewind(shader);
			//char* src = new char[len + 1];
			//fread(src, sizeof(char), len, shader);
			//src[len] = 0;
			//const char* vertexsrc = src;
			//fclose(shader);

			//fopen_s(&shader,fragmentpath.c_str(), "rb");

			//fseek(shader, 0L, SEEK_END);
			//len = ftell(shader);
			//rewind(shader);

			//src = new char[len + 1];
			//fread(src, sizeof(char), len, shader);
			//src[len] = '\0';
			//const char* fragmentsrc = src;
			//fclose(shader);
			//return { vertexsrc,fragmentsrc };
		}
		static std::string LoadShader(const std::string& path)
		{
			std::ifstream file(path);
			std::stringstream buffer;
			buffer << file.rdbuf();
			return std::move(buffer.str());

		}
		typedef std::chrono::high_resolution_clock Clock;
		static void LoadObj(const std::string& path,Mesh& mesh)
		{
			std::vector<glm::vec2> textureCoordinates;
			std::vector<glm::vec3> normalCoordinates;
			std::vector<glm::vec3> vertexCoordinates;

			std::vector<unsigned int> vertexIndices;
			std::vector<unsigned int> normalIndices;
			std::vector<unsigned int> textureIndices;
			

			auto start = Clock::now();
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
					normalCoordinates.emplace_back(x, y, z);
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
						auto localIt = it + 1; // empty string problem;
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
					it++;
					std::string number;
					while(it != line.end())
					{
						if (patternIt + 1 == pattern.end())
						{
							patternIt = pattern.begin();
							while(it != line.end() && *it == ' ') it++;
						}
						if (*patternIt == 'v')
						{
							number = Word(it, line.end(), *(patternIt + 1));
							vertexIndices.push_back(std::atoi(number.c_str()));
						}
						else if (*patternIt == 't')
						{
							number = Word(it, line.end(), *(patternIt + 1));
							textureIndices.push_back(std::atoi(number.c_str()));
						}
						else if (*patternIt == 'n')
						{
							number = Word(it, line.end(), *(patternIt + 1));
							normalIndices.push_back(std::atoi(number.c_str()));
						}
						else if (*patternIt == '/')
						{
							it++;
						}
						
						patternIt++;
					}
				}
				lineCount++;
			}
			auto end = Clock::now();
			WB_CORE_TRACE("File {0}: Loading Duration : {1} milliseconds",path, std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
		
			size_t memory = textureCoordinates.size() * sizeof(glm::vec2) + sizeof(glm::vec3) * (normalCoordinates.size() + vertexCoordinates.size())
				+ (vertexIndices.size() + textureIndices.size() + normalIndices.size()) * sizeof(unsigned int);
			WB_CORE_TRACE("File {0}: Memory used : {1} bytes",path,memory);
			/*for (size_t i = 0; i < vertexIndices.size() ;i++)
			{
				mesh.PushPosition(vertexCoordinates[vertexIndices[i]]);
				if(textureIndices.size() != 0)
					mesh.PushTextureCoordinate(textureCoordinates[textureIndices[i]]);
				if(normalCoordinates.size() != 0)
					mesh.PushNormal(normalCoordinates[normalIndices[i]]);
			}*/
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