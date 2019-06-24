#pragma once
#include "wbpch.h"
#include <stdio.h>
#include <stdlib.h>

namespace Wabisabi
{
	class ShaderLoader
	{
	public:
		static std::pair<const char*, const char*> Load(const std::string& vertexpath, const std::string& fragmentpath)
		{
			FILE* shader = NULL;
			fopen_s(&shader,vertexpath.c_str(), "rb");

			fseek(shader, 0L, SEEK_END);
			unsigned long len = ftell(shader);
			//int len = 0;
			/*char ch = 1;
			while (!feof(shader))
			{
				fread(&ch, sizeof(char), 1, shader);
				len++;
			}*/
			rewind(shader);
			char* src = new char[len + 1];
			fread(src, sizeof(char), len, shader);
			src[len] = 0;
			const char* vertexsrc = src;
			fclose(shader);

			fopen_s(&shader,fragmentpath.c_str(), "rb");

			fseek(shader, 0L, SEEK_END);
			len = ftell(shader);
			rewind(shader);

			src = new char[len + 1];
			fread(src, sizeof(char), len, shader);
			src[len] = '\0';
			const char* fragmentsrc = src;
			fclose(shader);
			return { vertexsrc,fragmentsrc };
		}
		static void Free(const char* vertexsrc, const char* fragmentsrc)
		{
			delete[] vertexsrc;
			delete[] fragmentsrc;
		}
	};
}