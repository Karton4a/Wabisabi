#include "wbpch.h"
#include "OpenglShader.h"
#include "Wabisabi/Log.h"
#include "Wabisabi/ShaderLoader.h"
#include <glad/glad.h>
namespace Wabisabi
{
	OpenglShader::OpenglShader(const std::string& vertexsrc, const std::string& fragmentsrc)
		:m_RendererId(0)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = vertexsrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			WB_CORE_ERROR("{0}", infoLog.data());
			WB_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentsrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			WB_CORE_ERROR("{0}", infoLog.data());
			WB_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererId = glCreateProgram();
		GLuint program = m_RendererId;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)& isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			WB_CORE_ERROR("{0}", infoLog.data());
			WB_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

		//TODO read about this
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	OpenglShader::~OpenglShader()
	{
		glDeleteProgram(m_RendererId);
	}
	void OpenglShader::Bind() const
	{
		glUseProgram(m_RendererId);
	}
	void OpenglShader::UnBind() const
	{
		glUseProgram(0);
	}
	int32_t OpenglShader::GetLocation(const std::string& name) const
	{
		int32_t location = glGetUniformLocation(m_RendererId, name.c_str());
		if (location == -1)
			WB_CORE_WARN("Uniform {0} doesn't exist or not used", name);
		return location;
	}
	void OpenglShader::SetUniform(const std::string& name, int32_t num)
	{
		int32_t loc = GetLocation(name);
		glUseProgram(m_RendererId);
		glUniform1i(loc, num);
	}
	void OpenglShader::SetUniform(const std::string& name, float_t num1, float_t num2, float_t num3, float_t num4)
	{
		int32_t loc = GetLocation(name);
		glUseProgram(m_RendererId);
		glUniform4f(loc, num1,num2, num3, num4);

	}
	void OpenglShader::SetUniform(const std::string& name, float_t num1, float_t num2, float_t num3)
	{
		int32_t loc = GetLocation(name);
		glUseProgram(m_RendererId);
		glUniform3f(loc, num1, num2, num3);
	}
	void OpenglShader::SetUniform(const std::string& name, const glm::mat4& matrix)
	{
		int32_t loc = GetLocation(name);
		glUseProgram(m_RendererId);
		
		glUniformMatrix4fv(loc, 1, GL_FALSE,&matrix[0][0]);
	}
	
}