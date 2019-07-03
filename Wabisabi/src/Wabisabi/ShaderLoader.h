#pragma once
#include "wbpch.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

namespace Wabisabi
{
	class ShaderLoader
	{
	public:
		static std::pair<std::string, std::string> LoadPair(const std::string& vertexpath, const std::string& fragmentpath)
		{
			std::string vertex = Preprocessor(Load(vertexpath),vertexpath);
			std::string fragment = Preprocessor(Load(fragmentpath),fragmentpath);
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
		static std::string Load(const std::string& path)
		{
			std::ifstream file(path);
			std::stringstream buffer;
			buffer << file.rdbuf();
			return std::move(buffer.str());

		}
		static void FreePair(const char* vertexsrc, const char* fragmentsrc)
		{
			delete[] vertexsrc;
			delete[] fragmentsrc;
		}
	private:
		static std::string Preprocessor(const std::string& src, const std::string& path)
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

				std::string subsource = ShaderLoader::Load(path);
				source.erase(found, end - found + 1);
				source.insert(found, subsource);

				found = source.find("#include", found + 1);
			}
			return std::move(source);
		}
	};
}